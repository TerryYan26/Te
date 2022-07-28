/*
; hash_table is a hash table that maps keys to values.
;  Where to look for info (e.g. LINE_SIZE)
; ● Checking memory errors
; ● load_table()
; ○ Reading input from a file
; ○ Input tokenization
; ○ Making datestr
; ○ hash()/hashFun
; ○ add_node()
; ● node_lookup()


*/

/* ;Describe target Hardware to the assembler */
.arch   armv6
.arm
.fpu	vfp
.syntax unified
.align 4
.bss
.data


/*;************************************************************************* */
.type   hashFun, %function // define as a function
.global hashFun            // export function name
.equ    FP_OFFSET, 28      // (regs - 1) * 4



/* ; How it's called from the c file hashFun((unsigned long)c, hash); */
hashFun:
    push {r4-r7, lr}
    mov r4, r0 
    mov r5, r1 // r5 = c
    ldr r6, =hash_table /* ; load the address of the hash table */
    ldr r7, [r6]        /* ; load the address of the hash table */
    ldr r0, [r7, r4]     /* ; load the address of the hash table */
    cmp r0, #0          /* ; check if the hash table is empty */
    beq hashFun_end     /* ; if it is, return 0 */
    /* ; if it isn't, loop through the hash table */
    /* ; Start a loop */
    b hashFun_loop
    /* ; End of loop */
    hashFun_end:
        pop {r4-r7, pc} /* ; return the hash value */
    /* ; End of function */
    hashFun_loop:
        /* ; Load the next node */
        ldr r0, [r0]
        cmp r0, #0 /* ; check if the node is empty if so, return 0 */
        beq hashFun_end
        /* ; if it isn't, compare the key */
        ldr r1, [r0]
        cmp r1, r5
        bne hashFun_loop
        /* ; if the key is the same, return the value */
        ldr r0, [r0, #4]
        /* ; End of function */
        pop {r4-r7, pc}




