/*KQUERYO - K-Query Online
no tags 

Given a sequence of n numbers a1, a2, ..., an and a number of k-queries. A k-query is a triple (i, j, k) (1 ≤ i ≤ j ≤ n). For each k-query (i, j, k), you have to return the number of elements greater than k in the subsequence ai, ai+1, ..., aj.
Input

    Line 1: n (1 ≤ n ≤ 30000).
    Line 2: n numbers a1, a2, ..., an (1 ≤ ai ≤ 109).
    Line 3: q (1 ≤ q ≤ 200000), the number of k- queries.
    In the next q lines, each line contains 3 numbers a, b, c representing a k-query. You should do the following:
        i = a xor last_ans
        j = b xor last_ans
        k = c xor last_ans
    After that 1 ≤ i ≤ j ≤ n, 1 ≤ k ≤ 109 holds.
    Where last_ans = the answer to the last query (for the first query it's 0).

Output

For each k-query (i, j, k), print the number of elements greater than k in the subsequence ai, ai+1, ..., aj in a single line.
Example

Input:
6
8 9 3 5 1 9
5
2 3 5
3 3 7
0 0 11
0 0 2
3 7 4

Output:
1
1
0
0
2

[Edited by EB]
There are invalid queries. Assume the following:

    if i < 1: i = 1
    if j > n: j = n
    if i > j: ans = 0

*/

#include <algorithm>
#include <cstdio>
#include <vector>

int arr[30005];
std::vector<int> tree[100005];

void build_tree(const int node, 
                const int a, 
                const int b)
{
    if (a == b) // Leaf node
    {
        tree[node].push_back(arr[a]);
    }
    else
    {
        int mid = (a + b) / 2;
        
        build_tree(node*2, a, mid);
        build_tree(node*2+1, mid+1, b);
        
        tree[node].reserve(tree[node*2].size() + tree[node*2+1].size());
        std::merge(std::begin(tree[node*2]), 
                   std::end(tree[node*2]), 
                   std::begin(tree[node*2+1]), 
                   std::end(tree[node*2+1]), 
                   std::back_inserter(tree[node]));
    }
}

std::size_t query_tree(const int node, 
                       const int a, 
                       const int b, 
                       const int i, 
                       const int j,
                       const int k)
{
    if(a > b || a > j || b < i) // Out of range
        return 0;
    else if (a >= i && b <= j) // Total Overlap
    {
        return std::distance(std::upper_bound(std::begin(tree[node]), 
                                              std::end(tree[node]), 
                                              k),
                             std::end(tree[node]));
    }
    else
    {
        // Partial overlap
        int mid = (a + b) / 2;
        
        auto left  = query_tree(node*2, a, mid, i, j, k);
        auto right = query_tree(node*2+1, mid+1, b, i, j, k);
            
        return left + right;
    }   
}

int main()
{    
    int n;
    std::scanf("%d", &n);
    
    for (int i = 0; i < n; ++i)
        std::scanf("%d", &arr[i]);
    
    build_tree(1, 0, n-1);
    
    int queries;
    std::scanf("%d", &queries);
    
    int las_ans = 0;
    while (queries--)
    {
        int l, r, k;
        std::scanf("%d %d %d", &l, &r, &k);
        
        // XOR as in description
        l ^= las_ans;
        r ^= las_ans;
        k ^= las_ans;
        
        // Query
        las_ans = query_tree(1, 0, n-1, l-1, r-1, k);
        
        // Print
        std::printf("%d\n", las_ans);
    }
    
    return 0;
}
