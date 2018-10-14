/*BREAKING - Number Breaking
#number-theory #prime-numbers-1 #number-theory-13 #math-number-theory

Every number is multiplication of some prime numbers. Prime number is a number which is only divided by 1 and itself. Here you are given a number n. You have to find the prime numbers whose multiplication makes this number.

For example, 12 is multiplication of prime numbers 2 and 3. 15 is multiplication of 3 and 5.
Input

First Line will contain the number of test cases T. Then each line will contain a single integer n.

Constraints: 1≤T≤1000, 2≤n≤1000000.
Output

For each test case print a single line which contains test case number and the prime numbers in ascending order separated by a single space whose multiplication make this number.
Example

Input:
3
12
42
84

Output:
Case 1: 2 3
Case 2: 2 3 7
Case 3: 2 3 7
*/

#include <cstdio>

#define MAX 1000033
#define LIM 1001
#define ifComp(x) (flagArr[x>>6]&(1<<((x>>1)&31)))
#define isComp(x) (flagArr[x>>6]|=(1<<((x>>1)&31)))


void BitSeive(int* output)
{
    int flagArr[MAX>>6] = {0};
    int i,j,k;
    
    for(i=3;i<LIM;i+=2)
        if(!ifComp(i))
            for(j=i*i,k=i<<1;j<MAX;j+=k)
                isComp(j);
       
    output[0] = 2;
    for(i=3,j=1;i<MAX;i+=2)
        if(!ifComp(i))
            output[j++] = i;
}


int main()
{       
    int sieve[78500];
    BitSeive(&sieve[0]);
    
    int tests;
    std::scanf("%d", &tests);
    
    for (int i = 1; i <= tests; ++i)
    {
        int num;
        std::scanf("%d", &num);
        
        std::printf("Case %d:", i);
        
        for (int idx = 0; idx < sizeof(sieve)/sizeof(sieve[0]) && num > 1; ++idx)
        {
            if (num % sieve[idx] == 0)
            {
                while (num % sieve[idx] == 0)
                    num /= sieve[idx];
                
                std::printf(" %d", sieve[idx]);
            }
        }
            
        std::printf("\n");
    }
    
    return 0;
}
