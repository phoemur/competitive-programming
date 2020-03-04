/*GSS3 - Can you answer these queries III
#tree

You are given a sequence A of N (N <= 50000) integers between -10000 and 10000. On this sequence you have to apply M (M <= 50000) operations:
modify the i-th element in the sequence or for given x y print max{Ai + Ai+1 + .. + Aj | x<=i<=j<=y }.
Input

The first line of input contains an integer N. The following line contains N integers, representing the sequence A1..AN.
The third line contains an integer M. The next M lines contain the operations in following form:
0 x y: modify Ax into y (|y|<=10000).
1 x y: print max{Ai + Ai+1 + .. + Aj | x<=i<=j<=y }.
Output

For each query, print an integer as the problem required.
Example

Input:
4
1 2 3 4
4
1 1 3
0 3 -3
1 2 4
1 3 3

Output:
6
4
-3

*/

#include <algorithm>
#include <cstdio>

constexpr static int MAXN = 1 << 16;
constexpr static int MN = -999999;

struct Node
{
    int preffix;
    int suffix;
    int sum;
    int best;
};

Node operator+(const Node& l, const Node& r) noexcept
{
    Node res;
    
    res.sum = l.sum + r.sum;
    res.preffix = std::max(l.preffix, l.sum + r.preffix);
    res.suffix  = std::max(r.suffix, r.sum + l.suffix);
    
    res.best = std::max(l.best, std::max(r.best, l.suffix + r.preffix));
    
    return res;
}

int arr[MAXN];
Node tree[MAXN << 2];

void build_tree(int node, int a, int b) noexcept
{
    if (a == b) // leaf node
    {
        tree[node].preffix = tree[node].suffix = tree[node].sum = tree[node].best = arr[a];
    }
    else
    {
        int mid = (a + b)/2;
        
        build_tree(node*2,   a,   mid); // left side
        build_tree(node*2+1, mid+1, b); // right side
        
        tree[node] = tree[node*2] + tree[node*2 + 1]; // Merge
    }
}

Node query_tree(int node, int a, int b, int l, int r) noexcept
{
    if (a > b || a > r || b < l) // No overlap
    {
        return Node {MN,MN,MN,MN};
    }
    else if (a >= l && b <= r) // Total Overlap
    {
        return tree[node];
    }
    else // Partial overlap
    {
        int mid = (a + b)/2;

        Node left  = query_tree(node*2,   a,     mid, l, r);
        Node right = query_tree(node*2+1, mid+1, b,   l, r);
        
        return left + right;
    }
}

void update_tree(int node, int a, int b, int idx, int val) noexcept // Point update
{
    if (a == b && a == idx)
    {
        tree[node].preffix = tree[node].suffix = tree[node].sum = tree[node].best = arr[idx] = val;
    }
    else
    {
        int mid = (a + b)/2;
        
        if (idx <= mid)
            update_tree(node*2, a, mid, idx, val);
        else // idx > mid
            update_tree(node*2+1, mid+1, b, idx, val);
        
        tree[node] = tree[node*2] + tree[node*2 + 1]; // Merge
    }
}


int main()
{    
    int n;
    std::scanf("%d", &n);
    
    for (int i = 0; i < n; ++i)
        std::scanf("%d", &arr[i]);
    
    build_tree(1, 0, n-1);
    
    int m;
    std::scanf("%d", &m);
    
    while (m--)
    {
        int a, l, r;
        std::scanf("%d %d %d", &a, &l, &r);
        
        if (a == 1)
        {
            Node res = query_tree(1, 0, n-1, l-1, r-1);
            std::printf("%d\n", res.best);
            
        }
        else // a == 0
        {
            update_tree(1, 0, n-1, l-1, r);
        }
    }
    
    return 0;
}
