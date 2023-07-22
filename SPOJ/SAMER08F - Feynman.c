#include <stdio.h>

int main(void)
{
    int num = 0;
    long out;
    // return m*(m+1)*(2*m+1)/6

    while (scanf("%d", &num) != 0 && num != 0)
    {
        __asm__ __volatile__ ("mov %1, %%eax\n\t" 
                              "mov %%rax, %%rbx\n\t" 
                              "inc %%rbx\n\t" 
                              "mov %%rax, %%rcx\n\t"
                              "imul $2, %%rcx\n\t" 
                              "inc %%rcx\n\t" 
                              "mul %%rbx\n\t" 
                              "mul %%rcx\n\t" 
                              "mov $0, %%rdx\n\t" 
                              "mov $6, %%rcx\n\t" 
                              "div %%rcx\n\t" 
                              "mov %%rax, %0\n\t"
                              : "=r" (out)
                              : "r"  (num)
                              : "rax", "rbx", "rcx", "rdx");

        printf("%ld\n", out);
    }

    return 0;
}
