
;@-------------------------------------------------------------------
;@-------------------------------------------------------------------

.globl _start
_start:
    b   reset

reset:
    mov sp,#0x42000000
    add sp,sp,#0x1000

    ;@ enable fpu
    mrc p15, 0, r0, c1, c0, 2
    orr r0,r0,#0x300000 ;@ single precision
    orr r0,r0,#0xC00000 ;@ double precision
    mcr p15, 0, r0, c1, c0, 2
    mov r0,#0x40000000
    fmxr fpexc,r0
    vmsr fpexc, r0

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

.globl fdummy
fdummy:
    bx lr

.globl ifdummy
ifdummy:
    vmov r0,s0
    bx lr

.globl vadd
vadd:
    vadd.f32 s0,s0,s1
    bx lr

.globl vdiv
vdiv:
    vdiv.f32 s0,s0,s1
    bx lr

.globl ftoi
ftoi:
    vcvtr.s32.f32 s2,s0
    vmov r0,s2
    bx lr

.globl itof
itof:
    vmov s0,r0
    vcvt.f32.u32 s0,s0
    bx lr

;@-------------------------------------------------------------------
;@-------------------------------------------------------------------
