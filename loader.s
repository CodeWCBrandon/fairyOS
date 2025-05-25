.set MAGIC_NUMBER, 0x1badb002 # magic number for GRUB
.set FLAGS, (1 << 0 | 1 << 1)
.set CHECKSUM, -(MAGIC_NUMBER + FLAGS)

.section .multiboot
    .long MAGIC_NUMBER
    .long FLAGS
    .long CHECKSUM

.section .text
    .global loader
    .extern kernelMain


loader:
    mov $kernel_stack, %esp
    push %eax
    push %ebx
    call kernelMain

_hang:
    cli
    hlt
    jmp _hang

.section .bss
    .space 2*1024*1024; # 2MiB spacing for stack pointer
    kernel_stack: