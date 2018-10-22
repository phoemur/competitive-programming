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

#define MAX 30001

struct Query {
    int l;
    int r;
    int k;
    int index;
};

int tree[1 << 15]; // BIT

void update_tree(int pos)
{
    while (pos <= MAX)
    {
        tree[pos] += 1;
        pos += (pos & -pos);
    }
}

int query_tree(int pos)
{
    int result = 0;
    
    while(pos > 0)
    {
        result += tree[pos];
        pos -= (pos & -pos);
    }
    
    return result;
}

int main()
{
    std::memset(tree, 0, sizeof(int) * (1 << 15));
    
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
    std::sort(std::begin(queries), std::end(queries), [](const Query& a, const Query& b){return a.k > b.k;});
    
    // Solve
    int pos = 0;
    for (int i = 0; i < q; ++i)
    {
        while (pos < n && arr[pos].first > queries[i].k)
        {
            update_tree(arr[pos].second + 1);
            ++pos;
        }
        
        result[queries[i].index] = query_tree(queries[i].r) - query_tree(queries[i].l-1);
    }
    
    // Print
    for (auto num: result)
        std::printf("%d\n", num);

    return 0;
}
