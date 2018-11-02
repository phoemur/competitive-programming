/*ANDROUND - AND Rounds
#tree

You are given a cyclic array A having N numbers. In an AND round, each element of the array A is replaced by the bitwise AND of itself, the previous element, and the next element in the array. All operations take place simultaneously. Can you calculate A after K such AND rounds ?
Input

The first line contains the number of test cases T (T <= 50).
There follow 2T lines, 2 per test case. The first line contains two space seperated integers N (3 <= N <= 20000) and K (1 <= K <= 1000000000). The next line contains N space seperated integers Ai (0 <= Ai <= 1000000000), which are the initial values of the elements in array A.
Output

Output T lines, one per test case. For each test case, output a space seperated list of N integers, specifying the contents of array A after K AND rounds.
Example

Sample Input:
2 
3 1 
1 2 3 
5 100 
1 11 111 1111 11111 
 
Sample Output:
0 0 0 
1 1 1 1 1

*/

#include <cstdio>

int arr[20001];
int tree[60003];

void build(int node, int lo, int hi)
{
    if (lo == hi)
        tree[node] = arr[lo];
    else
    {
        int mid = (lo + hi) / 2;
        
        build(node*2, lo, mid);
        build(node*2+1, mid+1, hi);
        
        tree[node] = tree[node*2] & tree[node*2+1];
    }
}

int query(int node, int lo, int hi, int i, int j)
{
    if (lo > hi || lo > j || hi < i)
        return -1; // All bits set
    else if (lo >= i && hi <= j)
        return tree[node];
    else
    {
        int mid = (lo + hi) / 2;
        
        int q1 = query(node*2, lo, mid, i, j);
        int q2 = query(node*2+1, mid+1, hi, i, j);
        
        return q1 & q2;
    }
}

int main()
{
    int tests;
    std::scanf("%d", &tests);
    
    while (tests--)
    {
        int n, k;
        std::scanf("%d %d", &n, &k);
        
        for (int i = 0; i < n; ++i)
            std::scanf("%d", &arr[i]);
        
        build(1, 0, n-1);
        
        for (int i = 0; i < n; ++i)
        {
            int result;
            int l = i - k;
            int r = i + k;
            
            if (k >= n/2)
                result = query(1, 0, n-1, 0, n-1);
            else if (l < 0)
                result = query(1, 0, n-1, 0, r) & query(1, 0, n-1, n+l, n-1);
            else if (r >= n)
                result = query(1, 0, n-1, l, n-1) & query(1, 0, n-1, 0, r-n);
            else
                result = query(1, 0, n-1, l, r);
            
            std::printf("%d ", result);    
        }
        
        std::printf("\n");
    }
    
    return 0;
}
