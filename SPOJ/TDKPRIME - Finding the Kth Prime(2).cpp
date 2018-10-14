/*TDKPRIME - Finding the Kth Prime
#sieve-of-eratosthenes

The problem statement is really simple. There are some queries. You are to give the answers.
Input

An integer stating the number of queries Q(equal to 50000), and Q lines follow, each containing one integer K between 1 and 5000000 inclusive.
Output

Q lines with the answer of each query: the Kth prime number.
Example

Input:
7
1
10
100
1000
10000
100000
1000000

Output:
2
29
541
7919
104729
1299709
15485863

*/

#include <cstdio>

#define MAX 86028157
#define LIM 9276
#define ifComp(x) (flagArr[x>>6]&(1<<((x>>1)&31)))
#define isComp(x) (flagArr[x>>6]|=(1<<((x>>1)&31)))


int sieve[5000001];

void BitSeive(int* output)
{
    int flagArr[MAX>>6] = {0};
    int i,j,k;
    for(i=3;i<LIM;i+=2)
    {
        if(!ifComp(i))
        {
            for(j=i*i,k=i<<1;j<MAX;j+=k)
                isComp(j);
        }
    }
       
    sieve[0] = 2;
    for(i=3,j=1;i<MAX;i+=2)
        if(!ifComp(i))
            output[j++] = i;
}


int main()
{
    int queries;
    std::scanf("%d", &queries);
       
    BitSeive(&sieve[0]);
    
    while (queries--)
    {
        int kth;
        std::scanf("%d", &kth);
        
        std::printf("%d\n", sieve[kth-1]);
    }
    
    return 0;
}
