/*SEGSQRSS - Sum of Squares with Segment Tree
#tree

Segment trees are extremely useful. In particular "Lazy Propagation" (i.e. see here, for example) allows one to compute sums over a range in O(lg(n)), and update ranges in O(lg(n)) as well. In this problem you will compute something much harder:

The sum of squares over a range with range updates of 2 types:

1) increment in a range

2) set all numbers the same in a range.
Input

There will be T (T <= 25) test cases in the input file. First line of the input contains two positive integers, N (N <= 100,000) and Q (Q <= 100,000). The next line contains N integers, each at most 1000. Each of the next Q lines starts with a number, which indicates the type of operation:

2 st nd -- return the sum of the squares of the numbers with indices in [st, nd] {i.e., from st to nd inclusive} (1 <= st <= nd <= N).

1 st nd x -- add "x" to all numbers with indices in [st, nd] (1 <= st <= nd <= N, and -1,000 <= x <= 1,000).

0 st nd x -- set all numbers with indices in [st, nd] to "x" (1 <= st <= nd <= N, and -1,000 <= x <= 1,000).
Output

For each test case output the “Case <caseno>:” in the first line and from the second line output the sum of squares for each operation of type 2. Intermediate overflow will not occur with proper use of 64-bit signed integer.
Example

Input:
2
4 5
1 2 3 4
2 1 4
0 3 4 1
2 1 4
1 3 4 1
2 1 4
1 1
1
2 1 1

Output:
Case 1:
30
7
13
Case 2:
1

*/

#include <cstdio>
#include <cstring>

int arr[100001]; // Input array
long tree[300003]; // Segment Tree

void build_tree(int node, int a, int b)
{
    if (a > b)
        return;
    else if (a == b) // Leaf Node
        tree[node] = arr[a] * arr[a];
    else
    {
        int mid = (a + b) / 2;
        
        build_tree(node*2, a, mid);
        build_tree(node*2+1, mid+1, b);
        
        tree[node] = tree[node*2] + tree[node*2+1];
    }
}

long range_query(int node, int a, int b, int i, int j)
{
    if (a > b || a > j || b < i) // No overlap
        return 0;
    else if (a >= i && b <= j) // Total overlap
        return tree[node];
    else // Partial overlap
    {
        // Divide
        int mid = (a + b) / 2;
        
        int left  = range_query(node*2, a, mid, i, j);
        int right = range_query(node*2+1, mid+1, b, i, j);
        
        // Conquer
        return left + right;
    }
}

void range_update_add(int node, int a, int b, int i, int j, int val)
{
    if (a > b || a > j || b < i)
        return;
    else if (a == b) // Leaf node
    {
        arr[a] += val;
        tree[node] = arr[a] * arr[a];
    }
    else
    {
        // Divide
        int mid = (a + b) / 2;
        
        range_update_add(node*2, a, mid, i, j, val);
        range_update_add(node*2+1, mid+1, b, i, j, val);
        
        //Conquer
        tree[node] = tree[node*2] + tree[node*2+1];
    }
}

void range_update_set(int node, int a, int b, int i, int j, int val)
{
    if (a > b || a > j || b < i)
        return;
    else if (a == b) // Leaf node
    {
        tree[node] = val * val;
    }
    else
    {
        // Divide
        int mid = (a + b) / 2;
        
        range_update_set(node*2, a, mid, i, j, val);
        range_update_set(node*2+1, mid+1, b, i, j, val);
        
        //Conquer
        tree[node] = tree[node*2] + tree[node*2+1];
    }
}

int main()
{
    int tests;
    std::scanf("%d", &tests);
    
    for (int cas = 1; cas <= tests; ++cas)
    {
        std::memset(tree, 0, sizeof(long) * 300003);
        
        int n, q;
        std::scanf("%d %d", &n, &q);
        
        for (int i = 0; i < n; ++i)
            std::scanf("%d", &arr[i]);
        
        build_tree(1, 0, n-1);
        
        std::printf("Case %d:\n", cas);
        while (q--)
        {
            int type;
            std::scanf("%d", &type);
            
            if (type == 2)
            {
                int l, r;
                std::scanf("%d %d", &l, &r);
                
                std::printf("%ld\n", range_query(1, 0, n-1, l-1, r-1));
            }
            else if (type == 1)
            {
                int l, r, val;
                std::scanf("%d %d %d", &l, &r, &val);
                
                range_update_add(1, 0, n-1, l-1, r-1, val);
            }
            else if (type == 0)
            {
                int l, r, val;
                std::scanf("%d %d %d", &l, &r, &val);
                
                range_update_set(1, 0, n-1, l-1, r-1, val);
            }
        }
    }
    
    return 0;
}
