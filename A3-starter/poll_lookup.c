/*
 * CSE30 Summer Session 1 '22 HW3
 * CSE30 username: cs30su122xxx (TODO: Fill in)
 */

#include "poll_lookup.h"

/*
 * !!! DO NOT EDIT THIS FUNCTION !!!
 * main
 *
 * Arguments: argc, argv
 *
 * Operation: Main driver for the program, calls other funttions to:
 *            parse the options, allocate the hash table, load the table, print
 *out the table stats
 *            and make print population stats of the desired city/state
 * Returns:   EXIT_SUCCESS if all ok, EXIT_FAILURE otherwise
 * !!! DO NOT EDIT THIS FUNCTION !!!
 */
int main(int argc, char *argv[]) {
  node **table;
  unsigned long size = TABLE_SIZE;
  // name of csv file
  char *filename;
  int info = 0;

  // Indicates days we want stats for/to remove
  char *date = NULL;
  char *del_date = NULL;

  // Parse options
  if (!parse_opts(argc, argv, &filename, &size, &info, &date, &del_date)) {
    return EXIT_FAILURE;
  }

  // Allocate space for table
  if ((table = calloc(size, sizeof(node *))) == NULL) {
    fprintf(stderr, "%s: Unable to allocate space for hash table\n", argv[0]);
    return EXIT_FAILURE;
  }

  // Load records from file
  if (load_table(table, size, filename)) {
    return EXIT_FAILURE;
  }

  // Delete data first
  if (del_date) {
    char *stripped_date = strip_date(del_date);
    if (stripped_date) { // no malloc fail
      delete_date(table, size, stripped_date);
      free(stripped_date);
    } else {
      return EXIT_FAILURE;
    }
  }

  // Produce data for a single date
  if (date) {
    char *stripped_date = strip_date(date);
    if (stripped_date) { // no malloc fail
      print_date_stats(table, size, stripped_date);
      free(stripped_date);
    } else {
      return EXIT_FAILURE;
    }
  }

  // Print metadata
  if (info)
    print_info(table, size);

  // Clean up
  delete_table(table, size);

  return EXIT_SUCCESS;
}

/*
 * !!! DO NOT EDIT THIS FUNCTION !!!
 * hash
 *
 * Arguments: a null terminated string
 *
 * Operation: calculates a hash value for the string
 *
 * returns:   the hash value
 * !!! DO NOT EDIT THIS FUNCTION !!!
 */
unsigned long hash(char *str) {
  unsigned long hash = 0;
  unsigned int c;
#ifdef C_HASH
  while ((c = (unsigned char)*str++) != '\0') {
    hash = c + (hash << 6) + (hash << 16) - hash;
  }
#else
  while ((c = (unsigned char)*str++) != '\0') {
    hash = hashFun((unsigned long)c, hash);
  }
#endif
  return hash;
}

/*
 * add_node
 *
 * Arguments: linked list pointer head, year, month, day, hour, pm25, temp
 */
node *add_node(node *front, int year, int month, int day, int hour, int pm25,
    int temp) {
  // TODO: Implement add_node
  node *new_node = malloc(sizeof(node));
  if (new_node == NULL) {
    fprintf(stderr, "Unable to allocate space for new node\n");
    return NULL;
  }
  new_node->year = year;
  new_node->month = month;
  new_node->day = day;
  new_node->hour = hour;
  new_node->pm25 = pm25;
  new_node->temp = temp;
  new_node->next = front;
  return new_node;
  
}

/*
 * print_date_stats
 * Print the average stats for this date
 *
 * Arguments: pointer to hash table, hash table size, date as a string in the
 *form YYYY-MM-DD
 */
void print_date_stats(node **table, unsigned long size, char *datestr) {
  // TODO: Implement print_data_stats
  int year, month, day;
  if (sscanf(datestr, "%d-%d-%d", &year, &month, &day) != 3) {
    fprintf(stderr, "Invalid date format\n");
    return;
  }
  int total_pm25 = 0;
  int total_temp = 0;
  int total_count = 0;
  unsigned int i;
  
  for (i = 0; i < size; i++) {
    node *curr = table[i];
    while (curr != NULL) {
      if (curr->year == year && curr->month == month && curr->day == day) {
        total_pm25 += curr->pm25;
        total_temp += curr->temp;
        total_count++;
      }
      curr = curr->next;
    }
  }
  if (total_count == 0) {
    fprintf(stderr, "No data for date %s\n", datestr);
    return;
  }
  printf("Average PM2.5 for %s: %.2f\n", datestr,
      (float)total_pm25 / total_count);
  printf("Average temperature for %s: %.2f\n", datestr,
      (float)total_temp / total_count);
}


/*
 * load_table
 * Allocate memory for the hash table of node*s
 *
 * Arguments: pointer to hash table, hash table size, file name
 */
int load_table(node **table, unsigned long size, char *filename) {
  // TODO: Implement load_table
  FILE *fp;
  if ((fp = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "Unable to open file %s\n", filename);
    return 1;
  }
  unsigned int size_read = size;
  char line[MAX_LINE_LENGTH];
  while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
    int year, month, day, hour, pm25, temp;
    if (sscanf(line, "%d-%d-%d %d:%d %d %i", &year, &month, &day, &hour,
        &pm25, &temp) != 6) {
      fprintf(stderr, "Invalid line format\n");
      return 1;
    }
    unsigned long hash_val = hash(line);
    node *new_node = add_node(table[hash_val], year, month, day, hour, pm25,
        temp);
    if (new_node == NULL) {
      fprintf(stderr, "Unable to allocate space for new node\n");
      return 1;
    }
    table[hash_val] = new_node;
  }
  fclose(fp);
  return 0;
}


/*
 * print_info
 *
 * Arguments: pointer to a hash table, number of elements
 */
void print_info(node **table, unsigned long size) {
  // TODO: Implement print_info
  /*
  printf("Table size: %lu\n", 
  printf("Total entries: %lu\n", 
  printf("Longest chain: %lu\n", 
  printf("Shortest chain: %lu\n", 
  printf("Empty buckets: %lu\n", 
  */
  unsigned int i;
  int max_chain = 0;
  int min_chain = INT_MAX;
  int empty_buckets = 0;
  int total_entries = 0;
  for (i = 0; i < size; i++) {
    int chain_length = 0;
    node *curr = table[i];
    while (curr != NULL) {
      chain_length++;
      curr = curr->next;
    }
    if (chain_length > max_chain)
      max_chain = chain_length;
    if (chain_length < min_chain)
      min_chain = chain_length;
    if (chain_length == 0)
      empty_buckets++;
    total_entries += chain_length;
  }
  printf("Table size: %lu\n", size);
  printf("Total entries: %d\n", total_entries);
  printf("Longest chain: %d\n", max_chain);
  printf("Shortest chain: %d\n", min_chain);
  printf("Empty buckets: %d\n", empty_buckets);
}

/*
 * delete_date
 * Delete all nodes associated with a given date of form YYYY-MM-DD
 * All leading zeros have been removed in the date string
 */
void delete_date(node **table, unsigned long size, char *datestr) {
  unsigned long hashval = hash(datestr) % size;
  node *chain = table[hashval];
  node *tmp, *prev = NULL;
  node* new_head = chain;

  const char split[] = "-";
  char *token = strtok(datestr, split);
  int cols[COL_DAY+1];
  int c = 0;
  while (token != NULL) {
    cols[c] = atoi(token);
    token = strtok(NULL, split);
    c++;
  }

  while (chain != NULL) {
    tmp = chain->next;
    // Delete if matching
    if (chain->year == cols[COL_YEAR] && chain->month == cols[COL_MONTH]
        && chain->day == cols[COL_DAY]) {
      // Only link previous if there was a previous
      if (prev) {
        prev->next = tmp;
      // No previous: this was the head, now new head is the one in front of us
      } else {
        new_head = tmp;
      }
      free(chain);
    // If not matching, don't delete and set prev as usual
    } else {
      prev = chain;
    }
    chain = tmp;
  }

  table[hashval] = new_head;
}


/*
 * delete_table
 *
 * Arguments: pointer to hash table, hash table array size
 */
void delete_table(node **table, unsigned long size) {
  unsigned int i;
  node *tmp;
  node *curr_tmp;

  for (i = 0; i < size; i++) {
    curr_tmp = table[i];
    while (curr_tmp != NULL) {
      tmp = curr_tmp->next;
      free(curr_tmp);
      curr_tmp = tmp;
    }
  }

  free(table);
}