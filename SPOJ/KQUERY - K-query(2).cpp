/*KQUERY - K-query
no tags 

English 	Vietnamese

Given a sequence of n numbers a1, a2, ..., an and a number of k- queries. A k-query is a triple (i, j, k) (1 ≤ i ≤ j ≤ n). For each k-query (i, j, k), you have to return the number of elements greater than k in the subsequence ai, ai+1, ..., aj.
Input

    Line 1: n (1 ≤ n ≤ 30000).
    Line 2: n numbers a1, a2, ..., an (1 ≤ ai ≤ 109).
    Line 3: q (1 ≤ q ≤ 200000), the number of k- queries.
    In the next q lines, each line contains 3 numbers i, j, k representing a k-query (1 ≤ i ≤ j ≤ n, 1 ≤ k ≤ 109).

Output

    For each k-query (i, j, k), print the number of elements greater than k in the subsequence ai, ai+1, ..., aj in a single line.

Example

Input
5
5 1 2 3 4
3
2 4 1
4 4 4
1 5 2 

Output
2
0
3 

*/

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>

struct Query {
    int l;
    int r;
    int k;
    int index;
};

int tree[90003]; // Segment Tree

void point_update_tree(int node, int a, int b, int idx)
{
    if (a == b && a == idx)
        tree[node] += 1;
    else
    {
        int mid = (a + b) / 2;
        
        if (idx <= mid)
            point_update_tree(node*2, a, mid, idx);
        else
            point_update_tree(node*2+1, mid+1, b, idx);
        
        tree[node] = tree[node*2] + tree[node*2+1];
    }
}

int range_sum_query(int node, int a, int b, int i, int j)
{
    if (a > b || a > j || b < i) // No overlap
        return 0;
    else if (a >= i && b <= j) // Total overlap
        return tree[node];
    else // Partial Overlap
    {
        // Divide
        int mid = (a + b) / 2;
        
        int left  = range_sum_query(node*2, a, mid, i, j);
        int right = range_sum_query(node*2+1, mid+1, b, i, j);
        
        // Conquer
        return left + right;
    }
}


int main()
{
    std::memset(tree, 0, sizeof(int) * 90003);
    
    int n;
    std::scanf("%d", &n);
    
    std::vector<std::pair<int,int>> arr (n); // pair [value, original index]
    
    for (int i = 0; i < n; ++i)
    {
        std::scanf("%d", &arr[i].first);
        arr[i].second = i;
    }
    
    // Sort arr by decreasing order of value
    std::sort(arr.rbegin(), arr.rend());
    
    int q;
    std::scanf("%d", &q);
    
    std::vector<Query> queries (q);
    std::vector<int> result (q);
    
    for (int i = 0; i < q; ++i)
    {
        std::scanf("%d%d%d", &queries[i].l, &queries[i].r, &queries[i].k);
        queries[i].index = i;
    }
    
    // Sort queries by decreasing order of k
    std::sort(std::begin(queries), 
              std::end(queries), 
              [](const Query& a, const Query& b)
              {
                  return a.k > b.k;
              });
    
    // Solve
    int pos = 0;
    for (int i = 0; i < q; ++i)
    {
        // Insert all indexes that arr[index] > k at the SegTree 
        while (pos < n && arr[pos].first > queries[i].k)
        {
            point_update_tree(1, 0, n-1, arr[pos].second);
            ++pos;
        }
        
        // Query
        result[queries[i].index] = range_sum_query(1, 0, n-1, queries[i].l - 1,  queries[i].r - 1);
    }
    
    // Print
    for (auto num: result)
        std::printf("%d\n", num);

    return 0;
}
