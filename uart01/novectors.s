
;@-------------------------------------------------------------------
;@-------------------------------------------------------------------

.globl _start
_start:
    b   reset

reset:
    mov r0,sp
    mov sp,#0x42000000
    add sp,sp,#0x1000


    ;@ enable fpu
    mrc p15, 0, r0, c1, c0, 2
    orr r0,r0,#0x300000 ;@ single precision
    orr r0,r0,#0xC00000 ;@ double precision
    mcr p15, 0, r0, c1, c0, 2
    mov r0,#0x40000000
    fmxr fpexc,r0

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

.globl CPACR
CPACR:
    mrc p15, 0, r0, c1, c0, 2
    bx lr

.globl ID_ISAR0
ID_ISAR0:
    mrc p15, 0, r0, c0, c2, 0
    bx lr


.globl FPSID
FPSID:
    VMRS r0, FPSID
    bx lr

;@-------------------------------------------------------------------
;@-------------------------------------------------------------------
