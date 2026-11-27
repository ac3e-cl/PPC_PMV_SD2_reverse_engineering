/* Reconstructed ARM assembly, explicitly authorized; not reconstructed C.
 * Complete HAL_ADC_ConfigChannel section, 0x08003d74..0x080045f3.
 * Instructions are mnemonics; .word is restricted to the two literal pools.
 * No original binary is included or read by the build. */
.syntax unified
.cpu cortex-m4
.fpu fpv4-sp-d16
.thumb
.section .text.FUN_08003d74,"ax",%progbits
.balign 4
.global FUN_08003d74
.type FUN_08003d74, %function
.thumb_func
FUN_08003d74:
    push       {r7, lr}                             @ 0x08003d74
    sub        sp, #216                             @ 0x08003d76
    add        r7, sp, #0                           @ 0x08003d78
    str        r0, [r7, #4]                         @ 0x08003d7a
    str        r1, [r7, #0]                         @ 0x08003d7c
    movs       r3, #0                               @ 0x08003d7e
    strb.w     r3, [r7, #215]                       @ 0x08003d80
    movs       r3, #0                               @ 0x08003d84
    str        r3, [r7, #12]                        @ 0x08003d86
    ldr        r3, [r7, #4]                         @ 0x08003d88
    ldrb.w     r3, [r3, #88]                        @ 0x08003d8a
    cmp        r3, #1                               @ 0x08003d8e
    bne.n      .L_08003d98                          @ 0x08003d90
    movs       r3, #2                               @ 0x08003d92
    b.w        .L_080045be                          @ 0x08003d94
.L_08003d98:
    ldr        r3, [r7, #4]                         @ 0x08003d98
    movs       r2, #1                               @ 0x08003d9a
    strb.w     r2, [r3, #88]                        @ 0x08003d9c
    ldr        r3, [r7, #4]                         @ 0x08003da0
    ldr        r3, [r3, #0]                         @ 0x08003da2
    mov        r0, r3                               @ 0x08003da4
    bl         FUN_08002f1c                         @ 0x08003da6
    mov        r3, r0                               @ 0x08003daa
    cmp        r3, #0                               @ 0x08003dac
    bne.w      .L_08004598                          @ 0x08003dae
    ldr        r3, [r7, #4]                         @ 0x08003db2
    ldr        r0, [r3, #0]                         @ 0x08003db4
    ldr        r3, [r7, #0]                         @ 0x08003db6
    ldr        r1, [r3, #4]                         @ 0x08003db8
    ldr        r3, [r7, #0]                         @ 0x08003dba
    ldr        r3, [r3, #0]                         @ 0x08003dbc
    mov        r2, r3                               @ 0x08003dbe
    bl         FUN_08002c3e                         @ 0x08003dc0
    ldr        r3, [r7, #4]                         @ 0x08003dc4
    ldr        r3, [r3, #0]                         @ 0x08003dc6
    mov        r0, r3                               @ 0x08003dc8
    bl         FUN_08002f1c                         @ 0x08003dca
    str.w      r0, [r7, #208]                       @ 0x08003dce
    ldr        r3, [r7, #4]                         @ 0x08003dd2
    ldr        r3, [r3, #0]                         @ 0x08003dd4
    mov        r0, r3                               @ 0x08003dd6
    bl         FUN_08002f6a                         @ 0x08003dd8
    str.w      r0, [r7, #204]                       @ 0x08003ddc
    ldr.w      r3, [r7, #208]                       @ 0x08003de0
    cmp        r3, #0                               @ 0x08003de4
    bne.w      .L_0800419c                          @ 0x08003de6
    ldr.w      r3, [r7, #204]                       @ 0x08003dea
    cmp        r3, #0                               @ 0x08003dee
    bne.w      .L_0800419c                          @ 0x08003df0
    ldr        r3, [r7, #0]                         @ 0x08003df4
    ldr        r3, [r3, #8]                         @ 0x08003df6
    cmp.w      r3, #2147483648                      @ 0x08003df8
    bne.n      .L_08003e1e                          @ 0x08003dfc
    ldr        r3, [r7, #4]                         @ 0x08003dfe
    ldr        r0, [r3, #0]                         @ 0x08003e00
    ldr        r3, [r7, #0]                         @ 0x08003e02
    ldr        r3, [r3, #0]                         @ 0x08003e04
    movs       r2, #0                               @ 0x08003e06
    mov        r1, r3                               @ 0x08003e08
    bl         FUN_08002cbc                         @ 0x08003e0a
    ldr        r3, [r7, #4]                         @ 0x08003e0e
    ldr        r3, [r3, #0]                         @ 0x08003e10
    mov.w      r1, #2147483648                      @ 0x08003e12
    mov        r0, r3                               @ 0x08003e16
    bl         FUN_08002bf2                         @ 0x08003e18
    b.n        .L_08003e3c                          @ 0x08003e1c
.L_08003e1e:
    ldr        r3, [r7, #4]                         @ 0x08003e1e
    ldr        r0, [r3, #0]                         @ 0x08003e20
    ldr        r3, [r7, #0]                         @ 0x08003e22
    ldr        r1, [r3, #0]                         @ 0x08003e24
    ldr        r3, [r7, #0]                         @ 0x08003e26
    ldr        r3, [r3, #8]                         @ 0x08003e28
    mov        r2, r3                               @ 0x08003e2a
    bl         FUN_08002cbc                         @ 0x08003e2c
    ldr        r3, [r7, #4]                         @ 0x08003e30
    ldr        r3, [r3, #0]                         @ 0x08003e32
    movs       r1, #0                               @ 0x08003e34
    mov        r0, r3                               @ 0x08003e36
    bl         FUN_08002bf2                         @ 0x08003e38
.L_08003e3c:
    ldr        r3, [r7, #0]                         @ 0x08003e3c
    ldr        r2, [r3, #20]                        @ 0x08003e3e
    ldr        r3, [r7, #4]                         @ 0x08003e40
    ldr        r3, [r3, #0]                         @ 0x08003e42
    ldr        r3, [r3, #12]                        @ 0x08003e44
    lsrs       r3, r3, #3                           @ 0x08003e46
    and.w      r3, r3, #3                           @ 0x08003e48
    lsls       r3, r3, #1                           @ 0x08003e4c
    lsl.w      r3, r2, r3                           @ 0x08003e4e
    str.w      r3, [r7, #200]                       @ 0x08003e52
    ldr        r3, [r7, #0]                         @ 0x08003e56
    ldr        r3, [r3, #16]                        @ 0x08003e58
    cmp        r3, #4                               @ 0x08003e5a
    beq.n      .L_08003ea4                          @ 0x08003e5c
    ldr        r3, [r7, #4]                         @ 0x08003e5e
    ldr        r0, [r3, #0]                         @ 0x08003e60
    ldr        r3, [r7, #0]                         @ 0x08003e62
    ldr        r1, [r3, #16]                        @ 0x08003e64
    ldr        r3, [r7, #0]                         @ 0x08003e66
    ldr        r2, [r3, #0]                         @ 0x08003e68
    ldr.w      r3, [r7, #200]                       @ 0x08003e6a
    bl         FUN_08002adc                         @ 0x08003e6e
    ldr        r3, [r7, #4]                         @ 0x08003e72
    ldr        r0, [r3, #0]                         @ 0x08003e74
    ldr        r3, [r7, #0]                         @ 0x08003e76
    ldr        r1, [r3, #16]                        @ 0x08003e78
    ldr        r3, [r7, #0]                         @ 0x08003e7a
    ldr        r3, [r3, #24]                        @ 0x08003e7c
    mov        r2, r3                               @ 0x08003e7e
    bl         FUN_08002b86                         @ 0x08003e80
    ldr        r3, [r7, #4]                         @ 0x08003e84
    ldr        r0, [r3, #0]                         @ 0x08003e86
    ldr        r3, [r7, #0]                         @ 0x08003e88
    ldr        r1, [r3, #16]                        @ 0x08003e8a
    ldr        r3, [r7, #0]                         @ 0x08003e8c
    ldrb       r3, [r3, #28]                        @ 0x08003e8e
    cmp        r3, #1                               @ 0x08003e90
    bne.n      .L_08003e9a                          @ 0x08003e92
    mov.w      r3, #33554432                        @ 0x08003e94
    b.n        .L_08003e9c                          @ 0x08003e98
.L_08003e9a:
    movs       r3, #0                               @ 0x08003e9a
.L_08003e9c:
    mov        r2, r3                               @ 0x08003e9c
    bl         FUN_08002bbc                         @ 0x08003e9e
    b.n        .L_0800419c                          @ 0x08003ea2
.L_08003ea4:
    ldr        r3, [r7, #4]                         @ 0x08003ea4
    ldr        r3, [r3, #0]                         @ 0x08003ea6
    movs       r1, #0                               @ 0x08003ea8
    mov        r0, r3                               @ 0x08003eaa
    bl         FUN_08002b24                         @ 0x08003eac
    mov        r3, r0                               @ 0x08003eb0
    ubfx       r3, r3, #0, #19                      @ 0x08003eb2
    cmp        r3, #0                               @ 0x08003eb6
    bne.n      .L_08003ed0                          @ 0x08003eb8
    ldr        r3, [r7, #4]                         @ 0x08003eba
    ldr        r3, [r3, #0]                         @ 0x08003ebc
    movs       r1, #0                               @ 0x08003ebe
    mov        r0, r3                               @ 0x08003ec0
    bl         FUN_08002b24                         @ 0x08003ec2
    mov        r3, r0                               @ 0x08003ec6
    lsrs       r3, r3, #26                          @ 0x08003ec8
    and.w      r2, r3, #31                          @ 0x08003eca
    b.n        .L_08003f0e                          @ 0x08003ece
.L_08003ed0:
    ldr        r3, [r7, #4]                         @ 0x08003ed0
    ldr        r3, [r3, #0]                         @ 0x08003ed2
    movs       r1, #0                               @ 0x08003ed4
    mov        r0, r3                               @ 0x08003ed6
    bl         FUN_08002b24                         @ 0x08003ed8
    mov        r3, r0                               @ 0x08003edc
    str.w      r3, [r7, #188]                       @ 0x08003ede
    ldr.w      r3, [r7, #188]                       @ 0x08003ee2
    rbit       r3, r3                               @ 0x08003ee6
    str.w      r3, [r7, #192]                       @ 0x08003eea
    ldr.w      r3, [r7, #192]                       @ 0x08003eee
    str.w      r3, [r7, #184]                       @ 0x08003ef2
    ldr.w      r3, [r7, #184]                       @ 0x08003ef6
    cmp        r3, #0                               @ 0x08003efa
    bne.n      .L_08003f02                          @ 0x08003efc
    movs       r3, #32                              @ 0x08003efe
    b.n        .L_08003f0c                          @ 0x08003f00
.L_08003f02:
    ldr.w      r3, [r7, #184]                       @ 0x08003f02
    clz        r3, r3                               @ 0x08003f06
    uxtb       r3, r3                               @ 0x08003f0a
.L_08003f0c:
    mov        r2, r3                               @ 0x08003f0c
.L_08003f0e:
    ldr        r3, [r7, #0]                         @ 0x08003f0e
    ldr        r3, [r3, #0]                         @ 0x08003f10
    ubfx       r3, r3, #0, #19                      @ 0x08003f12
    cmp        r3, #0                               @ 0x08003f16
    bne.n      .L_08003f26                          @ 0x08003f18
    ldr        r3, [r7, #0]                         @ 0x08003f1a
    ldr        r3, [r3, #0]                         @ 0x08003f1c
    lsrs       r3, r3, #26                          @ 0x08003f1e
    and.w      r3, r3, #31                          @ 0x08003f20
    b.n        .L_08003f58                          @ 0x08003f24
.L_08003f26:
    ldr        r3, [r7, #0]                         @ 0x08003f26
    ldr        r3, [r3, #0]                         @ 0x08003f28
    str.w      r3, [r7, #176]                       @ 0x08003f2a
    ldr.w      r3, [r7, #176]                       @ 0x08003f2e
    rbit       r3, r3                               @ 0x08003f32
    str.w      r3, [r7, #172]                       @ 0x08003f36
    ldr.w      r3, [r7, #172]                       @ 0x08003f3a
    str.w      r3, [r7, #180]                       @ 0x08003f3e
    ldr.w      r3, [r7, #180]                       @ 0x08003f42
    cmp        r3, #0                               @ 0x08003f46
    bne.n      .L_08003f4e                          @ 0x08003f48
    movs       r3, #32                              @ 0x08003f4a
    b.n        .L_08003f58                          @ 0x08003f4c
.L_08003f4e:
    ldr.w      r3, [r7, #180]                       @ 0x08003f4e
    clz        r3, r3                               @ 0x08003f52
    uxtb       r3, r3                               @ 0x08003f56
.L_08003f58:
    cmp        r2, r3                               @ 0x08003f58
    bne.n      .L_08003f6a                          @ 0x08003f5a
    ldr        r3, [r7, #4]                         @ 0x08003f5c
    ldr        r3, [r3, #0]                         @ 0x08003f5e
    movs       r2, #0                               @ 0x08003f60
    movs       r1, #0                               @ 0x08003f62
    mov        r0, r3                               @ 0x08003f64
    bl         FUN_08002b50                         @ 0x08003f66
.L_08003f6a:
    ldr        r3, [r7, #4]                         @ 0x08003f6a
    ldr        r3, [r3, #0]                         @ 0x08003f6c
    movs       r1, #1                               @ 0x08003f6e
    mov        r0, r3                               @ 0x08003f70
    bl         FUN_08002b24                         @ 0x08003f72
    mov        r3, r0                               @ 0x08003f76
    ubfx       r3, r3, #0, #19                      @ 0x08003f78
    cmp        r3, #0                               @ 0x08003f7c
    bne.n      .L_08003f96                          @ 0x08003f7e
    ldr        r3, [r7, #4]                         @ 0x08003f80
    ldr        r3, [r3, #0]                         @ 0x08003f82
    movs       r1, #1                               @ 0x08003f84
    mov        r0, r3                               @ 0x08003f86
    bl         FUN_08002b24                         @ 0x08003f88
    mov        r3, r0                               @ 0x08003f8c
    lsrs       r3, r3, #26                          @ 0x08003f8e
    and.w      r2, r3, #31                          @ 0x08003f90
    b.n        .L_08003fd4                          @ 0x08003f94
.L_08003f96:
    ldr        r3, [r7, #4]                         @ 0x08003f96
    ldr        r3, [r3, #0]                         @ 0x08003f98
    movs       r1, #1                               @ 0x08003f9a
    mov        r0, r3                               @ 0x08003f9c
    bl         FUN_08002b24                         @ 0x08003f9e
    mov        r3, r0                               @ 0x08003fa2
    str.w      r3, [r7, #164]                       @ 0x08003fa4
    ldr.w      r3, [r7, #164]                       @ 0x08003fa8
    rbit       r3, r3                               @ 0x08003fac
    str.w      r3, [r7, #160]                       @ 0x08003fb0
    ldr.w      r3, [r7, #160]                       @ 0x08003fb4
    str.w      r3, [r7, #168]                       @ 0x08003fb8
    ldr.w      r3, [r7, #168]                       @ 0x08003fbc
    cmp        r3, #0                               @ 0x08003fc0
    bne.n      .L_08003fc8                          @ 0x08003fc2
    movs       r3, #32                              @ 0x08003fc4
    b.n        .L_08003fd2                          @ 0x08003fc6
.L_08003fc8:
    ldr.w      r3, [r7, #168]                       @ 0x08003fc8
    clz        r3, r3                               @ 0x08003fcc
    uxtb       r3, r3                               @ 0x08003fd0
.L_08003fd2:
    mov        r2, r3                               @ 0x08003fd2
.L_08003fd4:
    ldr        r3, [r7, #0]                         @ 0x08003fd4
    ldr        r3, [r3, #0]                         @ 0x08003fd6
    ubfx       r3, r3, #0, #19                      @ 0x08003fd8
    cmp        r3, #0                               @ 0x08003fdc
    bne.n      .L_08003fec                          @ 0x08003fde
    ldr        r3, [r7, #0]                         @ 0x08003fe0
    ldr        r3, [r3, #0]                         @ 0x08003fe2
    lsrs       r3, r3, #26                          @ 0x08003fe4
    and.w      r3, r3, #31                          @ 0x08003fe6
    b.n        .L_0800401e                          @ 0x08003fea
.L_08003fec:
    ldr        r3, [r7, #0]                         @ 0x08003fec
    ldr        r3, [r3, #0]                         @ 0x08003fee
    str.w      r3, [r7, #152]                       @ 0x08003ff0
    ldr.w      r3, [r7, #152]                       @ 0x08003ff4
    rbit       r3, r3                               @ 0x08003ff8
    str.w      r3, [r7, #148]                       @ 0x08003ffc
    ldr.w      r3, [r7, #148]                       @ 0x08004000
    str.w      r3, [r7, #156]                       @ 0x08004004
    ldr.w      r3, [r7, #156]                       @ 0x08004008
    cmp        r3, #0                               @ 0x0800400c
    bne.n      .L_08004014                          @ 0x0800400e
    movs       r3, #32                              @ 0x08004010
    b.n        .L_0800401e                          @ 0x08004012
.L_08004014:
    ldr.w      r3, [r7, #156]                       @ 0x08004014
    clz        r3, r3                               @ 0x08004018
    uxtb       r3, r3                               @ 0x0800401c
.L_0800401e:
    cmp        r2, r3                               @ 0x0800401e
    bne.n      .L_08004030                          @ 0x08004020
    ldr        r3, [r7, #4]                         @ 0x08004022
    ldr        r3, [r3, #0]                         @ 0x08004024
    movs       r2, #0                               @ 0x08004026
    movs       r1, #1                               @ 0x08004028
    mov        r0, r3                               @ 0x0800402a
    bl         FUN_08002b50                         @ 0x0800402c
.L_08004030:
    ldr        r3, [r7, #4]                         @ 0x08004030
    ldr        r3, [r3, #0]                         @ 0x08004032
    movs       r1, #2                               @ 0x08004034
    mov        r0, r3                               @ 0x08004036
    bl         FUN_08002b24                         @ 0x08004038
    mov        r3, r0                               @ 0x0800403c
    ubfx       r3, r3, #0, #19                      @ 0x0800403e
    cmp        r3, #0                               @ 0x08004042
    bne.n      .L_0800405c                          @ 0x08004044
    ldr        r3, [r7, #4]                         @ 0x08004046
    ldr        r3, [r3, #0]                         @ 0x08004048
    movs       r1, #2                               @ 0x0800404a
    mov        r0, r3                               @ 0x0800404c
    bl         FUN_08002b24                         @ 0x0800404e
    mov        r3, r0                               @ 0x08004052
    lsrs       r3, r3, #26                          @ 0x08004054
    and.w      r2, r3, #31                          @ 0x08004056
    b.n        .L_0800409a                          @ 0x0800405a
.L_0800405c:
    ldr        r3, [r7, #4]                         @ 0x0800405c
    ldr        r3, [r3, #0]                         @ 0x0800405e
    movs       r1, #2                               @ 0x08004060
    mov        r0, r3                               @ 0x08004062
    bl         FUN_08002b24                         @ 0x08004064
    mov        r3, r0                               @ 0x08004068
    str.w      r3, [r7, #140]                       @ 0x0800406a
    ldr.w      r3, [r7, #140]                       @ 0x0800406e
    rbit       r3, r3                               @ 0x08004072
    str.w      r3, [r7, #136]                       @ 0x08004076
    ldr.w      r3, [r7, #136]                       @ 0x0800407a
    str.w      r3, [r7, #144]                       @ 0x0800407e
    ldr.w      r3, [r7, #144]                       @ 0x08004082
    cmp        r3, #0                               @ 0x08004086
    bne.n      .L_0800408e                          @ 0x08004088
    movs       r3, #32                              @ 0x0800408a
    b.n        .L_08004098                          @ 0x0800408c
.L_0800408e:
    ldr.w      r3, [r7, #144]                       @ 0x0800408e
    clz        r3, r3                               @ 0x08004092
    uxtb       r3, r3                               @ 0x08004096
.L_08004098:
    mov        r2, r3                               @ 0x08004098
.L_0800409a:
    ldr        r3, [r7, #0]                         @ 0x0800409a
    ldr        r3, [r3, #0]                         @ 0x0800409c
    ubfx       r3, r3, #0, #19                      @ 0x0800409e
    cmp        r3, #0                               @ 0x080040a2
    bne.n      .L_080040b2                          @ 0x080040a4
    ldr        r3, [r7, #0]                         @ 0x080040a6
    ldr        r3, [r3, #0]                         @ 0x080040a8
    lsrs       r3, r3, #26                          @ 0x080040aa
    and.w      r3, r3, #31                          @ 0x080040ac
    b.n        .L_080040e0                          @ 0x080040b0
.L_080040b2:
    ldr        r3, [r7, #0]                         @ 0x080040b2
    ldr        r3, [r3, #0]                         @ 0x080040b4
    str.w      r3, [r7, #128]                       @ 0x080040b6
    ldr.w      r3, [r7, #128]                       @ 0x080040ba
    rbit       r3, r3                               @ 0x080040be
    str        r3, [r7, #124]                       @ 0x080040c2
    ldr        r3, [r7, #124]                       @ 0x080040c4
    str.w      r3, [r7, #132]                       @ 0x080040c6
    ldr.w      r3, [r7, #132]                       @ 0x080040ca
    cmp        r3, #0                               @ 0x080040ce
    bne.n      .L_080040d6                          @ 0x080040d0
    movs       r3, #32                              @ 0x080040d2
    b.n        .L_080040e0                          @ 0x080040d4
.L_080040d6:
    ldr.w      r3, [r7, #132]                       @ 0x080040d6
    clz        r3, r3                               @ 0x080040da
    uxtb       r3, r3                               @ 0x080040de
.L_080040e0:
    cmp        r2, r3                               @ 0x080040e0
    bne.n      .L_080040f2                          @ 0x080040e2
    ldr        r3, [r7, #4]                         @ 0x080040e4
    ldr        r3, [r3, #0]                         @ 0x080040e6
    movs       r2, #0                               @ 0x080040e8
    movs       r1, #2                               @ 0x080040ea
    mov        r0, r3                               @ 0x080040ec
    bl         FUN_08002b50                         @ 0x080040ee
.L_080040f2:
    ldr        r3, [r7, #4]                         @ 0x080040f2
    ldr        r3, [r3, #0]                         @ 0x080040f4
    movs       r1, #3                               @ 0x080040f6
    mov        r0, r3                               @ 0x080040f8
    bl         FUN_08002b24                         @ 0x080040fa
    mov        r3, r0                               @ 0x080040fe
    ubfx       r3, r3, #0, #19                      @ 0x08004100
    cmp        r3, #0                               @ 0x08004104
    bne.n      .L_0800411e                          @ 0x08004106
    ldr        r3, [r7, #4]                         @ 0x08004108
    ldr        r3, [r3, #0]                         @ 0x0800410a
    movs       r1, #3                               @ 0x0800410c
    mov        r0, r3                               @ 0x0800410e
    bl         FUN_08002b24                         @ 0x08004110
    mov        r3, r0                               @ 0x08004114
    lsrs       r3, r3, #26                          @ 0x08004116
    and.w      r2, r3, #31                          @ 0x08004118
    b.n        .L_0800414e                          @ 0x0800411c
.L_0800411e:
    ldr        r3, [r7, #4]                         @ 0x0800411e
    ldr        r3, [r3, #0]                         @ 0x08004120
    movs       r1, #3                               @ 0x08004122
    mov        r0, r3                               @ 0x08004124
    bl         FUN_08002b24                         @ 0x08004126
    mov        r3, r0                               @ 0x0800412a
    str        r3, [r7, #116]                       @ 0x0800412c
    ldr        r3, [r7, #116]                       @ 0x0800412e
    rbit       r3, r3                               @ 0x08004130
    str        r3, [r7, #112]                       @ 0x08004134
    ldr        r3, [r7, #112]                       @ 0x08004136
    str        r3, [r7, #120]                       @ 0x08004138
    ldr        r3, [r7, #120]                       @ 0x0800413a
    cmp        r3, #0                               @ 0x0800413c
    bne.n      .L_08004144                          @ 0x0800413e
    movs       r3, #32                              @ 0x08004140
    b.n        .L_0800414c                          @ 0x08004142
.L_08004144:
    ldr        r3, [r7, #120]                       @ 0x08004144
    clz        r3, r3                               @ 0x08004146
    uxtb       r3, r3                               @ 0x0800414a
.L_0800414c:
    mov        r2, r3                               @ 0x0800414c
.L_0800414e:
    ldr        r3, [r7, #0]                         @ 0x0800414e
    ldr        r3, [r3, #0]                         @ 0x08004150
    ubfx       r3, r3, #0, #19                      @ 0x08004152
    cmp        r3, #0                               @ 0x08004156
    bne.n      .L_08004166                          @ 0x08004158
    ldr        r3, [r7, #0]                         @ 0x0800415a
    ldr        r3, [r3, #0]                         @ 0x0800415c
    lsrs       r3, r3, #26                          @ 0x0800415e
    and.w      r3, r3, #31                          @ 0x08004160
    b.n        .L_0800418a                          @ 0x08004164
.L_08004166:
    ldr        r3, [r7, #0]                         @ 0x08004166
    ldr        r3, [r3, #0]                         @ 0x08004168
    str        r3, [r7, #104]                       @ 0x0800416a
    ldr        r3, [r7, #104]                       @ 0x0800416c
    rbit       r3, r3                               @ 0x0800416e
    str        r3, [r7, #100]                       @ 0x08004172
    ldr        r3, [r7, #100]                       @ 0x08004174
    str        r3, [r7, #108]                       @ 0x08004176
    ldr        r3, [r7, #108]                       @ 0x08004178
    cmp        r3, #0                               @ 0x0800417a
    bne.n      .L_08004182                          @ 0x0800417c
    movs       r3, #32                              @ 0x0800417e
    b.n        .L_0800418a                          @ 0x08004180
.L_08004182:
    ldr        r3, [r7, #108]                       @ 0x08004182
    clz        r3, r3                               @ 0x08004184
    uxtb       r3, r3                               @ 0x08004188
.L_0800418a:
    cmp        r2, r3                               @ 0x0800418a
    bne.n      .L_0800419c                          @ 0x0800418c
    ldr        r3, [r7, #4]                         @ 0x0800418e
    ldr        r3, [r3, #0]                         @ 0x08004190
    movs       r2, #0                               @ 0x08004192
    movs       r1, #3                               @ 0x08004194
    mov        r0, r3                               @ 0x08004196
    bl         FUN_08002b50                         @ 0x08004198
.L_0800419c:
    ldr        r3, [r7, #4]                         @ 0x0800419c
    ldr        r3, [r3, #0]                         @ 0x0800419e
    mov        r0, r3                               @ 0x080041a0
    bl         FUN_08002e80                         @ 0x080041a2
    mov        r3, r0                               @ 0x080041a6
    cmp        r3, #0                               @ 0x080041a8
    bne.w      .L_08004428                          @ 0x080041aa
    ldr        r3, [r7, #4]                         @ 0x080041ae
    ldr        r0, [r3, #0]                         @ 0x080041b0
    ldr        r3, [r7, #0]                         @ 0x080041b2
    ldr        r1, [r3, #0]                         @ 0x080041b4
    ldr        r3, [r7, #0]                         @ 0x080041b6
    ldr        r3, [r3, #12]                        @ 0x080041b8
    mov        r2, r3                               @ 0x080041ba
    bl         FUN_08002d14                         @ 0x080041bc
    ldr        r3, [r7, #0]                         @ 0x080041c0
    ldr        r3, [r3, #12]                        @ 0x080041c2
    ldr        r2, .L_08004450                      @ 0x080041c4
    cmp        r3, r2                               @ 0x080041c6
    bne.w      .L_08004428                          @ 0x080041c8
    ldr        r3, [r7, #4]                         @ 0x080041cc
    ldr        r0, [r3, #0]                         @ 0x080041ce
    ldr        r3, [r7, #0]                         @ 0x080041d0
    ldr        r3, [r3, #0]                         @ 0x080041d2
    ubfx       r3, r3, #0, #19                      @ 0x080041d4
    cmp        r3, #0                               @ 0x080041d8
    bne.n      .L_080041f4                          @ 0x080041da
    ldr        r3, [r7, #0]                         @ 0x080041dc
    ldr        r3, [r3, #0]                         @ 0x080041de
    lsrs       r3, r3, #26                          @ 0x080041e0
    adds       r3, #1                               @ 0x080041e2
    and.w      r3, r3, #31                          @ 0x080041e4
    cmp        r3, #9                               @ 0x080041e8
    ite        ls                                   @ 0x080041ea
    movls      r3, #1                               @ 0x080041ec
    movhi      r3, #0                               @ 0x080041ee
    uxtb       r3, r3                               @ 0x080041f0
    b.n        .L_08004228                          @ 0x080041f2
.L_080041f4:
    ldr        r3, [r7, #0]                         @ 0x080041f4
    ldr        r3, [r3, #0]                         @ 0x080041f6
    str        r3, [r7, #92]                        @ 0x080041f8
    ldr        r3, [r7, #92]                        @ 0x080041fa
    rbit       r3, r3                               @ 0x080041fc
    str        r3, [r7, #88]                        @ 0x08004200
    ldr        r3, [r7, #88]                        @ 0x08004202
    str        r3, [r7, #96]                        @ 0x08004204
    ldr        r3, [r7, #96]                        @ 0x08004206
    cmp        r3, #0                               @ 0x08004208
    bne.n      .L_08004210                          @ 0x0800420a
    movs       r3, #32                              @ 0x0800420c
    b.n        .L_08004218                          @ 0x0800420e
.L_08004210:
    ldr        r3, [r7, #96]                        @ 0x08004210
    clz        r3, r3                               @ 0x08004212
    uxtb       r3, r3                               @ 0x08004216
.L_08004218:
    adds       r3, #1                               @ 0x08004218
    and.w      r3, r3, #31                          @ 0x0800421a
    cmp        r3, #9                               @ 0x0800421e
    ite        ls                                   @ 0x08004220
    movls      r3, #1                               @ 0x08004222
    movhi      r3, #0                               @ 0x08004224
    uxtb       r3, r3                               @ 0x08004226
.L_08004228:
    cmp        r3, #0                               @ 0x08004228
    beq.n      .L_08004320                          @ 0x0800422a
    ldr        r3, [r7, #0]                         @ 0x0800422c
    ldr        r3, [r3, #0]                         @ 0x0800422e
    ubfx       r3, r3, #0, #19                      @ 0x08004230
    cmp        r3, #0                               @ 0x08004234
    bne.n      .L_08004248                          @ 0x08004236
    ldr        r3, [r7, #0]                         @ 0x08004238
    ldr        r3, [r3, #0]                         @ 0x0800423a
    lsrs       r3, r3, #26                          @ 0x0800423c
    adds       r3, #1                               @ 0x0800423e
    lsls       r3, r3, #26                          @ 0x08004240
    and.w      r2, r3, #2080374784                  @ 0x08004242
    b.n        .L_08004274                          @ 0x08004246
.L_08004248:
    ldr        r3, [r7, #0]                         @ 0x08004248
    ldr        r3, [r3, #0]                         @ 0x0800424a
    str        r3, [r7, #80]                        @ 0x0800424c
    ldr        r3, [r7, #80]                        @ 0x0800424e
    rbit       r3, r3                               @ 0x08004250
    str        r3, [r7, #76]                        @ 0x08004254
    ldr        r3, [r7, #76]                        @ 0x08004256
    str        r3, [r7, #84]                        @ 0x08004258
    ldr        r3, [r7, #84]                        @ 0x0800425a
    cmp        r3, #0                               @ 0x0800425c
    bne.n      .L_08004264                          @ 0x0800425e
    movs       r3, #32                              @ 0x08004260
    b.n        .L_0800426c                          @ 0x08004262
.L_08004264:
    ldr        r3, [r7, #84]                        @ 0x08004264
    clz        r3, r3                               @ 0x08004266
    uxtb       r3, r3                               @ 0x0800426a
.L_0800426c:
    adds       r3, #1                               @ 0x0800426c
    lsls       r3, r3, #26                          @ 0x0800426e
    and.w      r2, r3, #2080374784                  @ 0x08004270
.L_08004274:
    ldr        r3, [r7, #0]                         @ 0x08004274
    ldr        r3, [r3, #0]                         @ 0x08004276
    ubfx       r3, r3, #0, #19                      @ 0x08004278
    cmp        r3, #0                               @ 0x0800427c
    bne.n      .L_08004294                          @ 0x0800427e
    ldr        r3, [r7, #0]                         @ 0x08004280
    ldr        r3, [r3, #0]                         @ 0x08004282
    lsrs       r3, r3, #26                          @ 0x08004284
    adds       r3, #1                               @ 0x08004286
    and.w      r3, r3, #31                          @ 0x08004288
    movs       r1, #1                               @ 0x0800428c
    lsl.w      r3, r1, r3                           @ 0x0800428e
    b.n        .L_080042c4                          @ 0x08004292
.L_08004294:
    ldr        r3, [r7, #0]                         @ 0x08004294
    ldr        r3, [r3, #0]                         @ 0x08004296
    str        r3, [r7, #68]                        @ 0x08004298
    ldr        r3, [r7, #68]                        @ 0x0800429a
    rbit       r3, r3                               @ 0x0800429c
    str        r3, [r7, #64]                        @ 0x080042a0
    ldr        r3, [r7, #64]                        @ 0x080042a2
    str        r3, [r7, #72]                        @ 0x080042a4
    ldr        r3, [r7, #72]                        @ 0x080042a6
    cmp        r3, #0                               @ 0x080042a8
    bne.n      .L_080042b0                          @ 0x080042aa
    movs       r3, #32                              @ 0x080042ac
    b.n        .L_080042b8                          @ 0x080042ae
.L_080042b0:
    ldr        r3, [r7, #72]                        @ 0x080042b0
    clz        r3, r3                               @ 0x080042b2
    uxtb       r3, r3                               @ 0x080042b6
.L_080042b8:
    adds       r3, #1                               @ 0x080042b8
    and.w      r3, r3, #31                          @ 0x080042ba
    movs       r1, #1                               @ 0x080042be
    lsl.w      r3, r1, r3                           @ 0x080042c0
.L_080042c4:
    orr.w      r1, r2, r3                           @ 0x080042c4
    ldr        r3, [r7, #0]                         @ 0x080042c8
    ldr        r3, [r3, #0]                         @ 0x080042ca
    ubfx       r3, r3, #0, #19                      @ 0x080042cc
    cmp        r3, #0                               @ 0x080042d0
    bne.n      .L_080042ea                          @ 0x080042d2
    ldr        r3, [r7, #0]                         @ 0x080042d4
    ldr        r3, [r3, #0]                         @ 0x080042d6
    lsrs       r3, r3, #26                          @ 0x080042d8
    adds       r3, #1                               @ 0x080042da
    and.w      r2, r3, #31                          @ 0x080042dc
    mov        r3, r2                               @ 0x080042e0
    lsls       r3, r3, #1                           @ 0x080042e2
    add        r3, r2                               @ 0x080042e4
    lsls       r3, r3, #20                          @ 0x080042e6
    b.n        .L_0800431c                          @ 0x080042e8
.L_080042ea:
    ldr        r3, [r7, #0]                         @ 0x080042ea
    ldr        r3, [r3, #0]                         @ 0x080042ec
    str        r3, [r7, #56]                        @ 0x080042ee
    ldr        r3, [r7, #56]                        @ 0x080042f0
    rbit       r3, r3                               @ 0x080042f2
    str        r3, [r7, #52]                        @ 0x080042f6
    ldr        r3, [r7, #52]                        @ 0x080042f8
    str        r3, [r7, #60]                        @ 0x080042fa
    ldr        r3, [r7, #60]                        @ 0x080042fc
    cmp        r3, #0                               @ 0x080042fe
    bne.n      .L_08004306                          @ 0x08004300
    movs       r3, #32                              @ 0x08004302
    b.n        .L_0800430e                          @ 0x08004304
.L_08004306:
    ldr        r3, [r7, #60]                        @ 0x08004306
    clz        r3, r3                               @ 0x08004308
    uxtb       r3, r3                               @ 0x0800430c
.L_0800430e:
    adds       r3, #1                               @ 0x0800430e
    and.w      r2, r3, #31                          @ 0x08004310
    mov        r3, r2                               @ 0x08004314
    lsls       r3, r3, #1                           @ 0x08004316
    add        r3, r2                               @ 0x08004318
    lsls       r3, r3, #20                          @ 0x0800431a
.L_0800431c:
    orrs       r3, r1                               @ 0x0800431c
    b.n        .L_0800441e                          @ 0x0800431e
.L_08004320:
    ldr        r3, [r7, #0]                         @ 0x08004320
    ldr        r3, [r3, #0]                         @ 0x08004322
    ubfx       r3, r3, #0, #19                      @ 0x08004324
    cmp        r3, #0                               @ 0x08004328
    bne.n      .L_0800433c                          @ 0x0800432a
    ldr        r3, [r7, #0]                         @ 0x0800432c
    ldr        r3, [r3, #0]                         @ 0x0800432e
    lsrs       r3, r3, #26                          @ 0x08004330
    adds       r3, #1                               @ 0x08004332
    lsls       r3, r3, #26                          @ 0x08004334
    and.w      r2, r3, #2080374784                  @ 0x08004336
    b.n        .L_08004368                          @ 0x0800433a
.L_0800433c:
    ldr        r3, [r7, #0]                         @ 0x0800433c
    ldr        r3, [r3, #0]                         @ 0x0800433e
    str        r3, [r7, #44]                        @ 0x08004340
    ldr        r3, [r7, #44]                        @ 0x08004342
    rbit       r3, r3                               @ 0x08004344
    str        r3, [r7, #40]                        @ 0x08004348
    ldr        r3, [r7, #40]                        @ 0x0800434a
    str        r3, [r7, #48]                        @ 0x0800434c
    ldr        r3, [r7, #48]                        @ 0x0800434e
    cmp        r3, #0                               @ 0x08004350
    bne.n      .L_08004358                          @ 0x08004352
    movs       r3, #32                              @ 0x08004354
    b.n        .L_08004360                          @ 0x08004356
.L_08004358:
    ldr        r3, [r7, #48]                        @ 0x08004358
    clz        r3, r3                               @ 0x0800435a
    uxtb       r3, r3                               @ 0x0800435e
.L_08004360:
    adds       r3, #1                               @ 0x08004360
    lsls       r3, r3, #26                          @ 0x08004362
    and.w      r2, r3, #2080374784                  @ 0x08004364
.L_08004368:
    ldr        r3, [r7, #0]                         @ 0x08004368
    ldr        r3, [r3, #0]                         @ 0x0800436a
    ubfx       r3, r3, #0, #19                      @ 0x0800436c
    cmp        r3, #0                               @ 0x08004370
    bne.n      .L_08004388                          @ 0x08004372
    ldr        r3, [r7, #0]                         @ 0x08004374
    ldr        r3, [r3, #0]                         @ 0x08004376
    lsrs       r3, r3, #26                          @ 0x08004378
    adds       r3, #1                               @ 0x0800437a
    and.w      r3, r3, #31                          @ 0x0800437c
    movs       r1, #1                               @ 0x08004380
    lsl.w      r3, r1, r3                           @ 0x08004382
    b.n        .L_080043b8                          @ 0x08004386
.L_08004388:
    ldr        r3, [r7, #0]                         @ 0x08004388
    ldr        r3, [r3, #0]                         @ 0x0800438a
    str        r3, [r7, #32]                        @ 0x0800438c
    ldr        r3, [r7, #32]                        @ 0x0800438e
    rbit       r3, r3                               @ 0x08004390
    str        r3, [r7, #28]                        @ 0x08004394
    ldr        r3, [r7, #28]                        @ 0x08004396
    str        r3, [r7, #36]                        @ 0x08004398
    ldr        r3, [r7, #36]                        @ 0x0800439a
    cmp        r3, #0                               @ 0x0800439c
    bne.n      .L_080043a4                          @ 0x0800439e
    movs       r3, #32                              @ 0x080043a0
    b.n        .L_080043ac                          @ 0x080043a2
.L_080043a4:
    ldr        r3, [r7, #36]                        @ 0x080043a4
    clz        r3, r3                               @ 0x080043a6
    uxtb       r3, r3                               @ 0x080043aa
.L_080043ac:
    adds       r3, #1                               @ 0x080043ac
    and.w      r3, r3, #31                          @ 0x080043ae
    movs       r1, #1                               @ 0x080043b2
    lsl.w      r3, r1, r3                           @ 0x080043b4
.L_080043b8:
    orr.w      r1, r2, r3                           @ 0x080043b8
    ldr        r3, [r7, #0]                         @ 0x080043bc
    ldr        r3, [r3, #0]                         @ 0x080043be
    ubfx       r3, r3, #0, #19                      @ 0x080043c0
    cmp        r3, #0                               @ 0x080043c4
    bne.n      .L_080043e4                          @ 0x080043c6
    ldr        r3, [r7, #0]                         @ 0x080043c8
    ldr        r3, [r3, #0]                         @ 0x080043ca
    lsrs       r3, r3, #26                          @ 0x080043cc
    adds       r3, #1                               @ 0x080043ce
    and.w      r2, r3, #31                          @ 0x080043d0
    mov        r3, r2                               @ 0x080043d4
    lsls       r3, r3, #1                           @ 0x080043d6
    add        r3, r2                               @ 0x080043d8
    subs       r3, #30                              @ 0x080043da
    lsls       r3, r3, #20                          @ 0x080043dc
    orr.w      r3, r3, #33554432                    @ 0x080043de
    b.n        .L_0800441c                          @ 0x080043e2
.L_080043e4:
    ldr        r3, [r7, #0]                         @ 0x080043e4
    ldr        r3, [r3, #0]                         @ 0x080043e6
    str        r3, [r7, #20]                        @ 0x080043e8
    ldr        r3, [r7, #20]                        @ 0x080043ea
    rbit       r3, r3                               @ 0x080043ec
    str        r3, [r7, #16]                        @ 0x080043f0
    ldr        r3, [r7, #16]                        @ 0x080043f2
    str        r3, [r7, #24]                        @ 0x080043f4
    ldr        r3, [r7, #24]                        @ 0x080043f6
    cmp        r3, #0                               @ 0x080043f8
    bne.n      .L_08004400                          @ 0x080043fa
    movs       r3, #32                              @ 0x080043fc
    b.n        .L_08004408                          @ 0x080043fe
.L_08004400:
    ldr        r3, [r7, #24]                        @ 0x08004400
    clz        r3, r3                               @ 0x08004402
    uxtb       r3, r3                               @ 0x08004406
.L_08004408:
    adds       r3, #1                               @ 0x08004408
    and.w      r2, r3, #31                          @ 0x0800440a
    mov        r3, r2                               @ 0x0800440e
    lsls       r3, r3, #1                           @ 0x08004410
    add        r3, r2                               @ 0x08004412
    subs       r3, #30                              @ 0x08004414
    lsls       r3, r3, #20                          @ 0x08004416
    orr.w      r3, r3, #33554432                    @ 0x08004418
.L_0800441c:
    orrs       r3, r1                               @ 0x0800441c
.L_0800441e:
    ldr        r2, [r7, #0]                         @ 0x0800441e
    ldr        r2, [r2, #8]                         @ 0x08004420
    mov        r1, r3                               @ 0x08004422
    bl         FUN_08002cbc                         @ 0x08004424
.L_08004428:
    ldr        r3, [r7, #0]                         @ 0x08004428
    ldr        r2, [r3, #0]                         @ 0x0800442a
    ldr        r3, .L_08004454                      @ 0x0800442c
    ands       r3, r2                               @ 0x0800442e
    cmp        r3, #0                               @ 0x08004430
    beq.w      .L_080045b2                          @ 0x08004432
    ldr        r3, [r7, #4]                         @ 0x08004436
    ldr        r3, [r3, #0]                         @ 0x08004438
    cmp.w      r3, #1342177280                      @ 0x0800443a
    beq.n      .L_0800444a                          @ 0x0800443e
    ldr        r3, [r7, #4]                         @ 0x08004440
    ldr        r3, [r3, #0]                         @ 0x08004442
    ldr        r2, .L_08004458                      @ 0x08004444
    cmp        r3, r2                               @ 0x08004446
    bne.n      .L_08004460                          @ 0x08004448
.L_0800444a:
    ldr        r3, .L_0800445c                      @ 0x0800444a
    b.n        .L_08004462                          @ 0x0800444c
    nop                                             @ 0x0800444e
.L_08004450:
    .word 0x407f0000           @ 0x08004450: peripheral base, channel encoding, or clock address
.L_08004454:
    .word 0x80080000           @ 0x08004454: peripheral base, channel encoding, or clock address
.L_08004458:
    .word 0x50000100           @ 0x08004458: peripheral base, channel encoding, or clock address
.L_0800445c:
    .word 0x50000300           @ 0x0800445c: peripheral base, channel encoding, or clock address
.L_08004460:
    ldr        r3, .L_080045c8                      @ 0x08004460
.L_08004462:
    mov        r0, r3                               @ 0x08004462
    bl         FUN_08002ac0                         @ 0x08004464
    str.w      r0, [r7, #196]                       @ 0x08004468
    ldr        r3, [r7, #0]                         @ 0x0800446c
    ldr        r3, [r3, #0]                         @ 0x0800446e
    ldr        r2, .L_080045cc                      @ 0x08004470
    cmp        r3, r2                               @ 0x08004472
    beq.n      .L_08004480                          @ 0x08004474
    ldr        r3, [r7, #0]                         @ 0x08004476
    ldr        r3, [r3, #0]                         @ 0x08004478
    ldr        r2, .L_080045d0                      @ 0x0800447a
    cmp        r3, r2                               @ 0x0800447c
    bne.n      .L_080044f6                          @ 0x0800447e
.L_08004480:
    ldr.w      r3, [r7, #196]                       @ 0x08004480
    and.w      r3, r3, #8388608                     @ 0x08004484
    cmp        r3, #0                               @ 0x08004488
    bne.n      .L_080044f6                          @ 0x0800448a
    ldr        r3, [r7, #4]                         @ 0x0800448c
    ldr        r3, [r3, #0]                         @ 0x0800448e
    cmp.w      r3, #1342177280                      @ 0x08004490
    beq.n      .L_080044a2                          @ 0x08004494
    ldr        r3, [r7, #4]                         @ 0x08004496
    ldr        r3, [r3, #0]                         @ 0x08004498
    ldr        r2, .L_080045d4                      @ 0x0800449a
    cmp        r3, r2                               @ 0x0800449c
    bne.w      .L_080045ac                          @ 0x0800449e
.L_080044a2:
    ldr        r3, [r7, #4]                         @ 0x080044a2
    ldr        r3, [r3, #0]                         @ 0x080044a4
    cmp.w      r3, #1342177280                      @ 0x080044a6
    beq.n      .L_080044b6                          @ 0x080044aa
    ldr        r3, [r7, #4]                         @ 0x080044ac
    ldr        r3, [r3, #0]                         @ 0x080044ae
    ldr        r2, .L_080045d8                      @ 0x080044b0
    cmp        r3, r2                               @ 0x080044b2
    bne.n      .L_080044ba                          @ 0x080044b4
.L_080044b6:
    ldr        r2, .L_080045dc                      @ 0x080044b6
    b.n        .L_080044bc                          @ 0x080044b8
.L_080044ba:
    ldr        r2, .L_080045c8                      @ 0x080044ba
.L_080044bc:
    ldr.w      r3, [r7, #196]                       @ 0x080044bc
    orr.w      r3, r3, #8388608                     @ 0x080044c0
    mov        r1, r3                               @ 0x080044c4
    mov        r0, r2                               @ 0x080044c6
    bl         FUN_08002a9a                         @ 0x080044c8
    ldr        r3, .L_080045e0                      @ 0x080044cc
    ldr        r3, [r3, #0]                         @ 0x080044ce
    lsrs       r3, r3, #6                           @ 0x080044d0
    ldr        r2, .L_080045e4                      @ 0x080044d2
    umull      r2, r3, r2, r3                       @ 0x080044d4
    lsrs       r3, r3, #6                           @ 0x080044d8
    adds       r2, r3, #1                           @ 0x080044da
    mov        r3, r2                               @ 0x080044dc
    lsls       r3, r3, #1                           @ 0x080044de
    add        r3, r2                               @ 0x080044e0
    lsls       r3, r3, #2                           @ 0x080044e2
    str        r3, [r7, #12]                        @ 0x080044e4
    b.n        .L_080044ee                          @ 0x080044e6
.L_080044e8:
    ldr        r3, [r7, #12]                        @ 0x080044e8
    subs       r3, #1                               @ 0x080044ea
    str        r3, [r7, #12]                        @ 0x080044ec
.L_080044ee:
    ldr        r3, [r7, #12]                        @ 0x080044ee
    cmp        r3, #0                               @ 0x080044f0
    bne.n      .L_080044e8                          @ 0x080044f2
    b.n        .L_080045ac                          @ 0x080044f4
.L_080044f6:
    ldr        r3, [r7, #0]                         @ 0x080044f6
    ldr        r3, [r3, #0]                         @ 0x080044f8
    ldr        r2, .L_080045e8                      @ 0x080044fa
    cmp        r3, r2                               @ 0x080044fc
    bne.n      .L_0800454c                          @ 0x080044fe
    ldr.w      r3, [r7, #196]                       @ 0x08004500
    and.w      r3, r3, #16777216                    @ 0x08004504
    cmp        r3, #0                               @ 0x08004508
    bne.n      .L_0800454c                          @ 0x0800450a
    ldr        r3, [r7, #4]                         @ 0x0800450c
    ldr        r3, [r3, #0]                         @ 0x0800450e
    ldr        r2, .L_080045d8                      @ 0x08004510
    cmp        r3, r2                               @ 0x08004512
    bne.n      .L_08004520                          @ 0x08004514
    ldr        r3, [r7, #4]                         @ 0x08004516
    ldr        r3, [r3, #0]                         @ 0x08004518
    ldr        r2, .L_080045ec                      @ 0x0800451a
    cmp        r3, r2                               @ 0x0800451c
    beq.n      .L_080045b0                          @ 0x0800451e
.L_08004520:
    ldr        r3, [r7, #4]                         @ 0x08004520
    ldr        r3, [r3, #0]                         @ 0x08004522
    cmp.w      r3, #1342177280                      @ 0x08004524
    beq.n      .L_08004534                          @ 0x08004528
    ldr        r3, [r7, #4]                         @ 0x0800452a
    ldr        r3, [r3, #0]                         @ 0x0800452c
    ldr        r2, .L_080045d8                      @ 0x0800452e
    cmp        r3, r2                               @ 0x08004530
    bne.n      .L_08004538                          @ 0x08004532
.L_08004534:
    ldr        r2, .L_080045dc                      @ 0x08004534
    b.n        .L_0800453a                          @ 0x08004536
.L_08004538:
    ldr        r2, .L_080045c8                      @ 0x08004538
.L_0800453a:
    ldr.w      r3, [r7, #196]                       @ 0x0800453a
    orr.w      r3, r3, #16777216                    @ 0x0800453e
    mov        r1, r3                               @ 0x08004542
    mov        r0, r2                               @ 0x08004544
    bl         FUN_08002a9a                         @ 0x08004546
    b.n        .L_080045b0                          @ 0x0800454a
.L_0800454c:
    ldr        r3, [r7, #0]                         @ 0x0800454c
    ldr        r3, [r3, #0]                         @ 0x0800454e
    ldr        r2, .L_080045f0                      @ 0x08004550
    cmp        r3, r2                               @ 0x08004552
    bne.n      .L_080045b2                          @ 0x08004554
    ldr.w      r3, [r7, #196]                       @ 0x08004556
    and.w      r3, r3, #4194304                     @ 0x0800455a
    cmp        r3, #0                               @ 0x0800455e
    bne.n      .L_080045b2                          @ 0x08004560
    ldr        r3, [r7, #4]                         @ 0x08004562
    ldr        r3, [r3, #0]                         @ 0x08004564
    ldr        r2, .L_080045d8                      @ 0x08004566
    cmp        r3, r2                               @ 0x08004568
    beq.n      .L_080045b2                          @ 0x0800456a
    ldr        r3, [r7, #4]                         @ 0x0800456c
    ldr        r3, [r3, #0]                         @ 0x0800456e
    cmp.w      r3, #1342177280                      @ 0x08004570
    beq.n      .L_08004580                          @ 0x08004574
    ldr        r3, [r7, #4]                         @ 0x08004576
    ldr        r3, [r3, #0]                         @ 0x08004578
    ldr        r2, .L_080045d8                      @ 0x0800457a
    cmp        r3, r2                               @ 0x0800457c
    bne.n      .L_08004584                          @ 0x0800457e
.L_08004580:
    ldr        r2, .L_080045dc                      @ 0x08004580
    b.n        .L_08004586                          @ 0x08004582
.L_08004584:
    ldr        r2, .L_080045c8                      @ 0x08004584
.L_08004586:
    ldr.w      r3, [r7, #196]                       @ 0x08004586
    orr.w      r3, r3, #4194304                     @ 0x0800458a
    mov        r1, r3                               @ 0x0800458e
    mov        r0, r2                               @ 0x08004590
    bl         FUN_08002a9a                         @ 0x08004592
    b.n        .L_080045b2                          @ 0x08004596
.L_08004598:
    ldr        r3, [r7, #4]                         @ 0x08004598
    ldr        r3, [r3, #92]                        @ 0x0800459a
    orr.w      r2, r3, #32                          @ 0x0800459c
    ldr        r3, [r7, #4]                         @ 0x080045a0
    str        r2, [r3, #92]                        @ 0x080045a2
    movs       r3, #1                               @ 0x080045a4
    strb.w     r3, [r7, #215]                       @ 0x080045a6
    b.n        .L_080045b2                          @ 0x080045aa
.L_080045ac:
    nop                                             @ 0x080045ac
    b.n        .L_080045b2                          @ 0x080045ae
.L_080045b0:
    nop                                             @ 0x080045b0
.L_080045b2:
    ldr        r3, [r7, #4]                         @ 0x080045b2
    movs       r2, #0                               @ 0x080045b4
    strb.w     r2, [r3, #88]                        @ 0x080045b6
    ldrb.w     r3, [r7, #215]                       @ 0x080045ba
.L_080045be:
    mov        r0, r3                               @ 0x080045be
    adds       r7, #216                             @ 0x080045c0
    mov        sp, r7                               @ 0x080045c2
    pop        {r7, pc}                             @ 0x080045c4
    nop                                             @ 0x080045c6
.L_080045c8:
    .word 0x50000700           @ 0x080045c8: peripheral base, channel encoding, or clock address
.L_080045cc:
    .word 0xc3210000           @ 0x080045cc: peripheral base, channel encoding, or clock address
.L_080045d0:
    .word 0x90c00010           @ 0x080045d0: peripheral base, channel encoding, or clock address
.L_080045d4:
    .word 0x50000600           @ 0x080045d4: peripheral base, channel encoding, or clock address
.L_080045d8:
    .word 0x50000100           @ 0x080045d8: peripheral base, channel encoding, or clock address
.L_080045dc:
    .word 0x50000300           @ 0x080045dc: peripheral base, channel encoding, or clock address
.L_080045e0:
    .word SystemCoreClock      @ 0x080045e0: peripheral base, channel encoding, or clock address
.L_080045e4:
    .word 0x053e2d63           @ 0x080045e4: division reciprocal
.L_080045e8:
    .word 0xc7520000           @ 0x080045e8: peripheral base, channel encoding, or clock address
.L_080045ec:
    .word 0x50000500           @ 0x080045ec: peripheral base, channel encoding, or clock address
.L_080045f0:
    .word 0xcb840000           @ 0x080045f0: peripheral base, channel encoding, or clock address
.size FUN_08003d74, .-FUN_08003d74
.section .note.GNU-stack,"",%progbits
