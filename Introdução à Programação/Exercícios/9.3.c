#include <stdio.h>
#include <locale.h>
#include "9.3.h"


int main() {
    setlocale(LC_ALL, "Portuguese");

    printf("%d\n", soma(4, 5));
    printf("%d\n", sub(4, 5));

    return 0;
}
