#include <stdio.h>
#include <stdlib.h>

void func1()
{
        printf("This is func1\n");
}

void func2()
{
        printf("This is func2\n");
}

int main(void)
{
        atexit(func1);
        atexit(func2);
        exit(EXIT_SUCCESS);
}
