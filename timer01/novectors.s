
;@-------------------------------------------------------------------
;@-------------------------------------------------------------------

.globl _start
_start:
    b   reset

reset:
    mov r0,sp
    mov sp,#0x42000000
    add sp,sp,#0x1000
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

.globl MIDR
MIDR:
    mrc p15, 0, r0, c0, c0, 0
    bx lr

.globl ID_PFR0
ID_PFR0:
    mrc p15, 0, r0, c0, c1, 0
    bx lr

.globl ID_PFR1
ID_PFR1:
    mrc p15, 0, r0, c0, c1, 1
    bx lr

.globl ID_DFR0
ID_DFR0:
    mrc p15, 0, r0, c0, c1, 2
    bx lr

.globl ID_AFR0
ID_AFR0:
    mrc p15, 0, r0, c0, c1, 3
    bx lr


;@-------------------------------------------------------------------
;@-------------------------------------------------------------------
