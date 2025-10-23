
#include <unistd.h>

#define EXIT_SUCCESS 0

int main(void)
{
    const char hello[] = "Hello, world!\n";
    write(STDOUT_FILENO, hello, sizeof(hello) -  1);
    return EXIT_SUCCESS;
}
