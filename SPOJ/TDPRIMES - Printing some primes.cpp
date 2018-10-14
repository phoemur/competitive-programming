/*TDPRIMES - Printing some primes
#sieve-of-eratosthenes

The problem statement is really simple. You are to write all primes less than 10^8
Input

There is not input
Output

To make the problem less output related write out only the 1st, 101st, 201st, ... 1st mod 100.
Example

Input:

Output:
2
547
1229
...
99995257
99996931
99998953

*/

#include <cstdio>

#define MAX 100000000
#define LIM 10000
#define LEN 5000000
#define ifComp(x) (flagArr[x>>6]&(1<<((x>>1)&31)))
#define isComp(x) (flagArr[x>>6]|=(1<<((x>>1)&31)))

int flagArr[MAX>>6];

void BitSeive()
{
    int i,j,k;
    for(i=3;i<LIM;i+=2)
    {
        if(!ifComp(i))
        {
            for(j=i*i,k=i<<1;j<MAX;j+=k)
                isComp(j);
        }
    }
       
    std::printf("2\n");
    for(i=3,j=2;i<MAX;i+=2)
        if(!ifComp(i))
        {
            if (j % 100 == 1)
                std::printf("%d\n",i);
            
            ++j;
        }
}

int main()
{
    BitSeive();
    
    return 0;
}
