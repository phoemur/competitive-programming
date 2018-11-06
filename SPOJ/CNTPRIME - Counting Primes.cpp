/*CNTPRIME - Counting Primes
#tree

Tortoise and Achilles are playing the Counting the Primes game. Achilles will give Tortoise some numbers, and some intervals, and then Tortoise needs to count the primes on those intervals. It is an easy game, but Tortoise is doing the counting slowly. Achilles is pissed off, so he has given you the task as you are a good programmer. For a twist, he has changed the game a little bit, that is he will give some intervals for counting the prime as well as he will give some intervals to change the numbers in that interval.

You are given an array of n elements. After that you will be given M commands. They are -

    0 x y v - you have to change all numbers in the range of x to y (inclusive) to v, where x and y are two indexes of the array.
    1 x y - output a line containing a single integer which is the number of primes between x and y (inclusive).

The array is indexed from 1 to n.

Input:

Input starts with an integer T (≤ 10), denoting the number of test cases.

Each case contains two integers n (1 ≤ n ≤ 104) and q (1 ≤ q ≤ 2*104). Then next line, you will be given N integers. After that each of the next q lines will contain a task in one of the following form:

    0 x y v (1 ≤ x ≤ y ≤ n, 2 ≤ v ≤ 106)
    1 x y (1 ≤ x ≤ y ≤ n)

And the numbers will be in range of [2, 106].

Output:

For each case, print the case number first. Then for each query '1 x y', print the number of primes between x and y [inclusively].

Sample Input
	

Output for Sample Input

1

5 3

78 2 13 12 3

1 1 2

0 4 4 5

1 1 5
	

Case 1:

1

4



Note:

    Use Faster IO like scanf,printf
    A prime number is a natural number greater than 1 that has no positive divisors other than 1 and itself. The first prime numbers are 2,3,5,7,11....2,3,5,7,11,…

*/

#include <algorithm>
#include <cstdio>
#include <cstring>

#define MAX 1002001
#define LIM 1001
#define ifComp(x) (flagArr[x>>6]&(1<<((x>>1)&31)))
#define isComp(x) (flagArr[x>>6]|=(1<<((x>>1)&31)))


int flagArr[15657]; // Bit sieve
int arr[30003]; // Input array
int tree[100001]; // Segment Tree
int lazy[100001]; // Lazy Propagation array

// Perform bitwise Sieve of Eratosthenes
void BitSeive()
{
    for(int i = 3; i < LIM; i += 2)
    {
        if(!ifComp(i))
        {
            int k = i << 1;
            for(int j=i*i; j < MAX ; j += k)
                isComp(j);
        }
    }
}

// Check if num is prime
inline bool isPrime(int num)
{
    return num == 2 || ((num & 1) && (!ifComp(num)));
}

// Build Segment tree for range sum query
void build_tree(int node, int lo, int hi)
{
    if (lo > hi)
        return;
    else if (lo == hi) // Leaf Node
    {
        if (isPrime(arr[lo]))
            tree[node] = 1;
        else
            tree[node] = 0;
    }
    else
    {
        int mid = (lo + hi) / 2;
        
        build_tree(node*2,      lo, mid);
        build_tree(node*2+1, mid+1,  hi);
        
        tree[node] = tree[node*2] + tree[node*2+1];
    }
}

// Propagate updates lazily down the tree
inline void push_down(int node, int a, int b)
{
    if(lazy[node] != -1)
    {
        if (isPrime(lazy[node]))
            tree[node] = b - a + 1;
        else
            tree[node] = 0;
        
        if (a != b)
            lazy[node*2] = lazy[node*2+1] = lazy[node];
        
        lazy[node] = -1;
    }
}

// Update tree from index i to j with val
void update_tree(int node, 
                 int a, 
                 int b, 
                 int i,
                 int j,
                 int val)
{
    push_down(node, a, b);

    if(a > b || a > j || b < i)
        return;
    else if(a >= i && b <= j)
    {
        // Update lazily
        if (isPrime(val))
            tree[node] = b - a + 1;
        else
            tree[node] = 0;
        
        if (a != b)
            lazy[node*2] = lazy[node*2+1] = val;
    }
    else
    {
        int mid = (a + b) / 2;
        
        update_tree(node*2, a, mid, i, j, val);
        update_tree(node*2+1, mid+1, b, i, j, val);
        
        tree[node] = tree[node*2] + tree[node*2+1];
    }
}

// Return the number of prime numbers between indexes i and j
int query(int node, int a, int b, int i, int j)
{
    push_down(node, a, b);
    
    if(a > b || a > j || b < i) // No overlap
        return 0;
    else if(a >= i && b <= j) // Total overlap
        return tree[node];
    else // Partial overlap
    {
        int mid = (a + b) / 2;
        int q1 = query(node*2, a, mid, i, j);
        int q2 = query(node*2+1, mid+1, b, i, j);

        return q1 + q2;
    }
}

int main()
{
    std::memset(flagArr, 0, sizeof(int) * 15625);
    BitSeive();
    
    int tests;
    std::scanf("%d", &tests);
    
    for (int cas = 1; cas <= tests; ++cas)
    {
        int n, q;
        std::scanf("%d %d", &n, &q);
        
        std::memset(tree, 0, sizeof(int) * 100001);
        std::fill(lazy, lazy+100001, -1);
        
        for (int i = 0; i < n; ++i)
            std::scanf("%d", &arr[i]);
        
        build_tree(1, 0, n-1);
        
        std::printf("Case %d:\n", cas);
        while (q--)
        {
            int op, x, y, v;
            std::scanf("%d", &op);
            
            if (op == 0)
            {
                std::scanf("%d %d %d", &x, &y, &v);
                
                update_tree(1, 0, n-1, x-1, y-1, v);
            }
            else
            {
                std::scanf("%d %d", &x, &y);
                std::printf("%d\n", query(1, 0, n-1, x-1, y-1));
            }
        }
    }
    
    return 0;
}
