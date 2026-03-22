#include "runtime/__mem.h"

/* Source: https://github.com/Swiftshine/key/blob/d72e17891992c16fcf04a42c2d73005e0db71d86/src/PowerPC_EABI_Support/Runtime/__mem.c */
/* Handwritten asm; attempted to match as C here: https://decomp.me/scratch/R3nOu */
// clang-format off
asm void *memcpy(register void *dest, register const void *src, register size_t size)
{
    cmplwi cr1, size, 0
    beqlr cr1

    cmplw cr1, src, dest
    blt cr1, reverse
    beqlr cr1

    li r6, 0x80
    cmplw cr5, size, r6
    blt cr5, test_word_alignment

    clrlwi r9, src, 0x1d
    clrlwi r10, dest, 0x1d
    subf r8, r10, dest

    dcbt 0, src

    xor. r11, r10, r9
    bne byte_setup

    andi. r10, r10, 7
    beq+ double_copy_setup

    li r6, 8
    subf r9, r9, r6
    addi r8, dest, 0
    mtctr r9
    subf size, r9, size

byte_loop_double_align:
    lbz r9, 0(src)
    addi src, src, 1
    stb r9, 0(r8)
    addi r8, r8, 1
    bdnz byte_loop_double_align

double_copy_setup:
    srwi r6, size, 5
    mtctr r6

double_loop:
    lfd f1, 0(src)
    lfd f2, 8(src)
    lfd f3, 0x10(src)
    lfd f4, 0x18(src)
    addi src, src, 0x20
    stfd f1, 0(r8)
    stfd f2, 8(r8)
    stfd f3, 0x10(r8)
    stfd f4, 0x18(r8)

    addi r8, r8, 0x20
    bdnz double_loop
    andi. r6, size, 0x1f
    beqlr
    addi src, src, -1
    mtctr r6
    addi r8, r8, -1

byte_loop_1:
    lbzu r9, 1(src)
    stbu r9, 1(r8)
    bdnz byte_loop_1
    blr

test_word_alignment:
    li r6, 0x14
    cmplw cr5, size, r6
    ble cr5, byte_setup
    clrlwi r9, src, 0x1e
    clrlwi r10, dest, 0x1e
    xor. r11, r10, r9
    bne byte_setup
    li r6, 4
    subf r9, r9, r6
    addi r8, dest, 0
    subf size, r9, size
    mtctr r9

byte_loop_word_align:
    lbz r9, 0(src)
    addi src, src, 1
    stb r9, 0(r8)
    addi r8, r8, 1
    bdnz byte_loop_word_align

word_copy_setup:
    srwi r6, size, 4
    mtctr r6

word_loop:
    lwz r9, 0(src)
    lwz r10, 4(src)
    lwz r11, 8(src)
    lwz r12, 0xc(src)
    addi src, src, 0x10
    stw r9, 0(r8)
    stw r10, 4(r8)
    stw r11, 8(r8)
    stw r12, 0xc(r8)
    addi r8, r8, 0x10
    bdnz word_loop

    andi. r6, size, 0xf
    beqlr
    addi src, src, -1
    mtctr r6
    addi r8, r8, -1

byte_loop_2:
    lbzu r9, 1(src)
    stbu r9, 1(r8)
    bdnz byte_loop_2
    blr

byte_setup:
    addi r7, src, -1
    addi r8, dest, -1
    mtctr size

byte_loop_3:
    lbzu r9, 1(r7)
    stbu r9, 1(r8)
    bdnz byte_loop_3
    blr

reverse:
    add src, src, size
    add r12, dest, size
    li r6, 0x80
    cmplw cr5, size, r6
    blt cr5, reverse_test_word_alignment
    clrlwi r9, src, 0x1d
    clrlwi r10, r12, 0x1d
    xor. r11, r10, r9
    bne reverse_byte_setup
    andi. r10, r10, 7
    beq+ reverse_double_copy_setup
    mtctr r10

reverse_byte_loop_double_align:
    lbzu r9, -1(src)
    stbu r9, -1(r12)
    bdnz reverse_byte_loop_double_align

reverse_double_copy_setup:
    subf size, r10, size
    srwi r6, size, 5
    mtctr r6

reverse_double_loop:
    lfd f1, -8(src)
    lfd f2, -0x10(src)
    lfd f3, -0x18(src)
    lfd f4, -0x20(src)
    addi src, src, -32
    stfd f1, -8(r12)
    stfd f2, -0x10(r12)
    stfd f3, -0x18(r12)
    stfdu f4, -0x20(r12)

    bdnz reverse_double_loop

    andi. r6, size, 0x1f
    beqlr
    mtctr r6

reverse_byte_loop_1:
    lbzu r9, -1(src)
    stbu r9, -1(r12)
    bdnz reverse_byte_loop_1
    blr

reverse_test_word_alignment:
    li r6, 0x14
    cmplw cr5, size, r6
    ble cr5, reverse_byte_setup
    clrlwi r9, src, 0x1e
    clrlwi r10, r12, 0x1e
    xor. r11, r10, r9
    bne reverse_byte_setup
    andi. r10, r10, 7
    beq+ reverse_word_loop_setup
    mtctr r10

reverse_byte_loop_word_align:
    lbzu r9, -1(src)
    stbu r9, -1(r12)
    bdnz reverse_byte_loop_word_align

reverse_word_loop_setup:
    subf size, r10, size
    srwi r6, size, 4
    mtctr r6

reverse_word_loop:
    lwz r9, -4(src)
    lwz r10, -8(src)
    lwz r11, -0xc(src)
    lwz r8, -0x10(src)
    addi src, src, -16
    stw r9, -4(r12)
    stw r10, -8(r12)
    stw r11, -0xc(r12)
    stwu r8, -0x10(r12)
    bdnz reverse_word_loop

    andi. r6, size, 0xf
    beqlr
    mtctr r6

reverse_byte_loop_2:
    lbzu r9, -1(src)
    stbu r9, -1(r12)
    bdnz reverse_byte_loop_2
    blr

reverse_byte_setup:
    mtctr size

reverse_byte_loop_3:
    lbzu r9, -1(src)
    stbu r9, -1(r12)
    bdnz reverse_byte_loop_3
    blr
}
// clang-format on

void __fill_mem(void *dest, int ch, size_t count)
{
    int work;
    char *bdst = (char *)dest;
    int *wdst = (int *)dest;
    unsigned int cc = (unsigned char)ch;

    bdst--;

    // Optimize when filling more than 32B
    if (count >= 32)
    {
        // How many bytes dst is word-unaligned
        work = ~(u32)(bdst) & 3;

        // Byte-store to hit word alignment
        if (work)
        {
            count -= work;
            do
            {
                *++bdst = cc;
            } while (--work);
        }

        // Build word-sized value
        if (cc)
        {
            cc = (cc << 24) | (cc << 16) | (cc << 8) | cc;
        }

        // 32-byte store
        work = count / 32;
        wdst = (int *)(bdst - 3);
        if (work)
        {
            do
            {
                wdst[1] = cc;
                wdst[2] = cc;
                wdst[3] = cc;
                wdst[4] = cc;
                wdst[5] = cc;
                wdst[6] = cc;
                wdst[7] = cc;
                wdst[8] = cc;
                wdst += 8;
            } while (--work);
        }

        // 4-byte (word) store
        work = (count / 4) & 7;
        if (work)
        {
            do
            {
                *++wdst = cc;
            } while (--work);
        }

        bdst = (char *)wdst + 3;
        count &= 3;
    }

    // Remaining byte-copy, or caller specified < 32B store
    if (count > 0)
    {
        do
        {
            *++bdst = cc;
        } while (--count);
    }
}

void *memset(void *dest, int ch, size_t count)
{
    __fill_mem(dest, ch, count);
    return dest;
}

DECL_WEAK size_t strlen(const char *s)
{
    const u8 *p = (u8 *)s - 1;
    size_t len = -1;

    do
    {
        len++;
    } while (*++p);

    return len;
}
