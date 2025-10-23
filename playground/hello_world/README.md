use `ldd` to check for linked dynamic libraries on the compiled runnable.

compile `ex2.c` with the `-static` flag

> for no stl:<br>
> compile `ex2.c` with the `-nostdlib` flag<br>
> will segfault cause of exit - solution in `main.c`.

compile `main.c` with `-static -nostdlib -fno-stack-protector` flags
