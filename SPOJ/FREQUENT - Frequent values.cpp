/*FREQUENT - Frequent values
#tree

You are given a sequence of n integers a1 , a2 , ... , an in non-decreasing order. In addition to that, you are given several queries consisting of indices i and j (1 ≤ i ≤ j ≤ n). For each query, determine the most frequent value among the integers ai , ... , aj.
Input Specification

The input consists of several test cases. Each test case starts with a line containing two integers n and q (1 ≤ n, q ≤ 100000). The next line contains n integers a1 , ... , an (-100000 ≤ ai ≤ 100000, for each i ∈ {1, ..., n}) separated by spaces. You can assume that for each i ∈ {1, ..., n-1}: ai ≤ ai+1. The following q lines contain one query each, consisting of two integers i and j (1 ≤ i ≤ j ≤ n), which indicate the boundary indices for the query.

The last test case is followed by a line containing a single 0.
Output Specification

For each query, print one line with one integer: The number of occurrences of the most frequent value within the given range.
Sample Input

10 3
-1 -1 1 1 1 1 3 10 10 10
2 3
1 10
5 10
0

Sample Output

1
4
3

A naive algorithm may not run in time! 
*/

#include <algorithm>
#include <cstdint>
#include <cstdio>

struct Node {
    std::int64_t best;
    std::int64_t suff_freq;
    std::int64_t pref_freq;
    std::int64_t suff_num;
    std::int64_t pref_num;
};

std::int64_t arr[100001];
Node tree[300003];

// Node merge function -> https://pastebin.com/PWkdRmVz
Node operator+(const Node& lhs, const Node& rhs)
{
    Node res {};
    
    if (lhs.suff_num == rhs.pref_num)
    {
        res.best = std::max({lhs.best, 
                             rhs.best, 
                             lhs.suff_freq + rhs.pref_freq});
        
        if (lhs.pref_num == lhs.suff_num) 
            res.pref_freq = lhs.suff_freq + rhs.pref_freq;
        else
            res.pref_freq = lhs.pref_freq;
        
        if (rhs.pref_num == rhs.suff_num)
            res.suff_freq = lhs.suff_freq + rhs.pref_freq;
        else
            res.suff_freq = rhs.suff_freq;
    }
    else
    {
        res.best = std::max(lhs.best, rhs.best);
        res.pref_freq = lhs.pref_freq;
        res.suff_freq = rhs.suff_freq;
    }
    
    res.pref_num = lhs.pref_num;
    res.suff_num = rhs.suff_num;
    
    return res;
}

void build(int node, int a, int b)
{
    if (a > b)
        return;
    else if (a == b)
    {
        tree[node].pref_freq = tree[node].suff_freq = tree[node].best = 1;
        tree[node].pref_num = tree[node].suff_num = arr[a];
    }
    else
    {
        int mid = (a + b) / 2;
        
        build(node*2, a, mid);
        build(node*2+1, mid+1, b);
        
        tree[node] = tree[node*2] + tree[node*2+1];
    }
}

Node query(int node, int a, int b, int i, int j)
{
    if (a > b || a > j || b < i) // No overlap
        return Node{};
    else if (a >= i && b <= j) // Total overlap
        return tree[node];
    else // Partial Overlap
    {
        int mid = (a + b) / 2;
        
        auto left  = query(node*2, a, mid, i, j);
        auto right = query(node*2+1, mid+1, b, i, j);
        
        return left + right;
    }
}

int main()
{
    int n;
    while (std::scanf("%d", &n) != EOF && n != 0)
    {
        int q;
        std::scanf("%d", &q);
        
        for (int i = 0; i < n; ++i)
            std::scanf("%lld", &arr[i]);
    
        build(1, 0, n-1);
    
        while (q--)
        {
            int l, r;
            std::scanf("%d %d", &l, &r);
            
            auto res = query(1, 0, n-1, l-1, r-1);
            std::printf("%lld\n", res.best);
        }
    }
    
    return 0;
}
