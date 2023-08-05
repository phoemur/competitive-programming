/* PFACT - Prime Factors
no tags 

Bhelu is very fond of prime numbers as well as factors of a number. So, he wishes to find all the prime factors of a number.

Your task is very simple. You just have to print all the prime factors in increasing order of all the numbers up to 10^5.

Note: Bhelu is smart and he knows that 1 is not a prime. So start printing prime factors of n such that (2 <= n <= 10^5).
Input

There is no input.
Output

10^5 - 1 lines containing prime factors of numbers, one line for each number in the following format:

<number>: <all the prime factors>
Example

Output:
2: 2
3: 3
4: 2
5: 5
6: 2 3
...
100000: 2 5

*/ 

#include <stdio.h>
#include <stdint.h>

int main(int argc, char** argv)
{
    for (int i = 2; i <= 100000; ++i)
    {
        int num = i;
        printf("%d:", num);

        // Check evens 
        if ((num & 1) == 0)
        {
            printf(" 2");

            while ((num & 1) == 0)
            {
                num >>= 1; 
            }
        }

        // Check rest
        for (int64_t j = 3; j*j <= num; j += 2)
        {
            if (num % j == 0)
            {
                printf(" %ld", j);

                while (num % j == 0)
                {
                    num /= j;
                }
            }
        }

        // Here prime numbers
        if (num > 1)
        {
            printf(" %d", num);
        }

        printf("\n");
    }

    return 0;
}
