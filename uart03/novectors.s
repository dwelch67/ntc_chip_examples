
;@-------------------------------------------------------------------
;@-------------------------------------------------------------------

.globl _start
_start:
    b   reset

reset:
    mov r0,sp
    mov sp,#0x8000
    bl notmain
hang: b hang

.globl PUT32
PUT32:
    str r1,[r0]
    bx lr

.globl GET32
GET32:
    ldr r0,[r0]
    bx lr

.globl ASMDELAY
ASMDELAY:
    subs r0,r0,#1
    bne ASMDELAY
    bx lr


.globl CPSR
CPSR:
    mrs r0,cpsr
    bx lr

;@-------------------------------------------------------------------
;@-------------------------------------------------------------------
