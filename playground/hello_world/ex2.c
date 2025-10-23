#define EXIT_SUCCESS 0

int main(void)
{
    const char hello[] = "Hello, world!\n";

    asm volatile(
        "mov $1, %%rax\n"     // syscall number for write
        "mov $1, %%rdi\n"     // stdout (fd = 1)
        "lea %0, %%rsi\n"     // address of message
        "mov $14, %%rdx\n"    // length
        "syscall\n\t"
        :
        : "m"(hello)
        : "%rax", "%rdi", "%rsi", "%rdx"
    );

    return EXIT_SUCCESS;
}
