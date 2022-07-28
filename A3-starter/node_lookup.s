/*
; ARM 
; node* node_lookup()
; Arguments:
; node* front → The current head of the linked list chain
; int year → year
; int month → month
; int day → day
; int hour → hour
; Operation:
; ● Searches the linked list chain for a node that matches the year year, the month
; month, the day day and hour hour.
; ● Returns the pointer to the node with matching data, otherwise, return NULL.
; Simplifying node_lookup():
; ● The function node_lookup() takes 5 parameters. The first four parameters will be in
; R0 to R3. The fifth parameter is stored by the caller just above your stackframe (fp). So
; you can access the fifth parameter as [fp, NCOLS_OFFSET]. What will be the value
; of NCOLS_OFFSET?
*/
/* ;file header */
.arch armv6     
.arm            
.fpu vfp        
.syntax unified 
.file "node_lookup.s"
.text
.global node_lookup
.type node_lookup, %function
.align 4
.equ FP_OFF, 4

node_lookup:
    /*;Function prologue */
    stmfd sp!, {r4-r11}
    /*;Function body */
    /*; Declare local variables */
    mov r0, r0 /*; r0 = year */
    mov r1, r1 /*; r1 = month */
    mov r2, r2 /*; r2 = day */
    mov r3, r3 /*; r3 = hour */
    mov r4, r4 /*; r4 = front */
    mov r5, r5 /*; r5 = node */
    mov r6, r6 /*; r6 = node_ptr */

    /*; Search the linked list chain for a node that matches the year year, the month, the day day and hour hour. */
    /*; If a node is found, return the pointer to the node with matching data, otherwise, return NULL. */
    /*; If a node is not found, return NULL. */
    /*; If a node is found, return the pointer to the node with matching data, otherwise, return NULL. */

    /* ;Check if the linked list is empty */
    cmp r4, #0
    beq node_lookup_empty /*; If the linked list is empty, return NULL */
    /* ;Else, continue */
    /* ;Check if the node is the head of the linked list */
    cmp r4, r6 /*; r4 = front, r6 = node_ptr */
    beq node_lookup_head /*; If the node is the head of the linked list, return the pointer to the node with matching data */
    /* ;Else, continue */
    /* ;Check if the node is the tail of the linked list */
    cmp r6, #0 /*; r6 = node_ptr */
    beq node_lookup_tail /*; If the node is the tail of the linked list, return the pointer to the node with matching data */
    /* ;Else, continue */
    /* ;Check if the node is in the middle of the linked list */
    cmp r4, r6 /*; r4 = front, r6 = node_ptr */
    bne node_lookup_middle /*; If the node is in the middle of the linked list, return the pointer to the node with matching data */
    /* ;Else, continue */

    /* ;If the node is not found, return NULL */
    mov r0, #0 /*; r0 = NULL */
    b node_lookup_end /*; Return NULL */

    /* ;If the node is the head of the linked list */
    node_lookup_head: /*; r4 = front, r6 = node_ptr */
        /* ;The node is the head of the linked list */
        mov r5, r4 /*; r5 = front */
        mov r6, r4 /*; r6 = node_ptr */
        ldr r7, [r6, #0] /*; r7 = node */
        cmp r7, #0 /*; r7 = node */
        beq node_lookup_end /*; If the node is NULL, return NULL */
    
    node_lookup_end: /*; r0 = year, r1 = month, r2 = day, r3 = hour, r4 = front, r5 = front, r6 = node_ptr, r7 = node */
        /* ;Function epilogue */
        ldmfd sp!, {r4-r11}
        bx lr /*; Return */

    /* ;If the node is the tail of the linked list */
    node_lookup_tail: /*; r4 = front, r6 = node_ptr */
        /* ;The node is the tail of the linked list */
        mov r5, r4 /*; r5 = front */
        mov r6, r4 /*; r6 = node_ptr */
        ldr r7, [r6, #0] /*; r7 = node */
        cmp r7, #0 /*; r7 = node */
        beq node_lookup_end /*; If the node is NULL, return NULL */

    node_lookup_middle: /*; r4 = front, r6 = node_ptr */
        /* ;The node is in the middle of the linked list */
        mov r5, r4 /*; r5 = front */
        mov r6, r4 /*; r6 = node_ptr */
        ldr r7, [r6, #0] /*; r7 = node */
        cmp r7, #0 /*; r7 = node */
        beq node_lookup_end /*; If the node is NULL, return NULL */
        

    /* ;If the node is not found, return NULL */
    node_lookup_empty: /*; r4 = front, r6 = node_ptr */
        /* ;The linked list is empty */
        mov r0, #0 /*; r0 = NULL */
        b node_lookup_end /*; Return NULL */

    /* ;If the node is found, return the pointer to the node with matching data */
    node_lookup_found: /*; r0 = year, r1 = month, r2 = day, r3 = hour, r4 = front, r5 = front, r6 = node_ptr, r7 = node */
        /* ;The node is found */
        mov r0, r7 /*; r0 = node */
        b node_lookup_end /*; Return the pointer to the node with matching data */
        
    /* ;Function epilogue */
    ldmfd sp!, {r4-r11}
    bx lr /*; Return */

    /* ;Function footer */
    .size node_lookup, (. - node_lookup)

    /* ;File footer */
    .section .note.GNU-stack,"",%progbits
.end node_lookup