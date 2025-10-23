int _start(void) // true entry-point
{
    const char hello[] = "Hello, world!\n";

    asm volatile(
        "mov $1, %%rax\n\t"     // syscall number for write
        "mov $1, %%rdi\n\t"     // stdout (fd = 1)
        "lea %0, %%rsi\n\t"     // address of message
        "mov $14, %%rdx\n\t"    // length
        "syscall\n\t"
        :
        : "m"(hello)
        : "%rax", "%rdi", "%rsi", "%rdx"
    );

    // Exit syscall
    asm volatile(
        "mov $60, %%rax\n\t"  // SYS_exit
        "mov $0, %%rdi\n\t"   // exit code = 0
        "syscall\n\t"
        ::: "%rax", "%rdi"
    );

    // Never called
    return 0;
}
