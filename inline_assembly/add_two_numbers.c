#include <stdio.h>

int main(void)
{
        int foo = 10, bar = 15;
        asm volatile("addl  %%ebx,%%eax"
                             :"=a"(foo)
                             :"a"(foo), "b"(bar)
                             );
        printf("foo+bar=%d\n", foo);
        return 0;
}
