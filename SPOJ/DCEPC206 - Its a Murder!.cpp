/*DCEPC206 - Its a Murder!
#tree #binary-search

Once detective Saikat was solving a murder case. While going to the crime scene he took the stairs and saw that a number is written on every stair. He found it suspicious and decides to remember all the numbers that he has seen till now. While remembering the numbers he found that he can find some pattern in those numbers. So he decides that for each number on the stairs he will note down the sum of all the numbers previously seen on the stairs which are smaller than the present number. Calculate the sum of all the numbers written on his notes diary.
Input

First line gives T, number of test cases.

2T lines follow.

First line gives you the number of stairs N

Next line gives you N numbers written on the stairs.
Output

For each test case output one line giving the final sum for each test case.
Constraints

T<=10

1<=N<=10^5

All numbers will be between 0 and 10^6.
Example

Input:
1
5
1 5 3 6 4

Output:
15

*/

#include <cstdio>
#include <cstring>

#define SIZE 1000005

long tree[SIZE];


void update(int idx, int val)
{
    for(;idx < SIZE; idx += idx & (-idx))
         tree[idx] += val;               
}

long query(int idx)
{
    long res = 0;
    
    for (;idx > 0; idx -= idx & (-idx))
        res += tree[idx];
    
    return res;
}

int main()
{    
    int tests;
    std::scanf("%d", &tests);

    while (tests--)
    {
        int n;
        std::scanf("%d", &n);

        std::memset(tree, 0, sizeof(long) * SIZE);

        long res = 0;
        for (int i = 0; i < n; ++i)
        {
            int x;
            std::scanf("%d", &x);

            if (x == 0) continue;

            update(x, x);
            res += query(x-1);
        }

        std::printf("%ld\n", res);
    }

    return 0;
}
