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

#include <cstdio>

template<typename T>
constexpr T maximum(T t1, T t2)
{
    return t1 > t2 ? t1: t2;
}

template<typename T, typename... Args>
constexpr T maximum(T t1, Args... args)
{
    return maximum(t1, maximum(args...));
}

struct Node {
    int preffix;
    int suffix;
    int sum;
    int best;
};

static const int MAX = 1 << 16;
int arr[MAX];
Node tree[MAX << 1];

inline Node merge(const Node& left, const Node& right)
{
    Node res {};
        
    res.sum = left.sum + right.sum;
    res.preffix = maximum(left.preffix, left.sum + right.preffix);
    res.suffix  = maximum(right.suffix, right.sum + left.suffix);
    res.best = maximum(left.best, 
                       right.best, 
                       left.suffix + right.preffix);
        
    return res;
}

void build_tree(int node, int a, int b) 
{    
    if(a == b) // Leaf node
    { 
        tree[node].preffix = tree[node].suffix = tree[node].sum = tree[node].best = arr[a];
    }
    else
    {
        build_tree(node*2, a, (a+b)/2); // Init left child
        build_tree(node*2+1, 1+(a+b)/2, b); // Init right child
        
        tree[node] = merge(tree[node*2], tree[node*2+1]);
    }
}

Node query_tree(int node, int a, int b, int i, int j) 
{
    if(a==i && b==j)
        return tree[node];

    int mid = (a + b) / 2;
    
    if(j <= mid) 
        return query_tree(2*node, a, mid, i, j);
	else if (i > mid) 
        return query_tree(2*node+1, mid+1, b, i, j);
    else
    {
        Node q1 = query_tree(2*node, a, mid, i, mid); // Query left child
        Node q2 = query_tree(2*node + 1, mid+1, b, mid+1, j); // Query right child

        return merge(q1, q2);
    }
}

void update_tree(int node, int i, int j, int idx, int val)
{
    if (i == j && j == idx)
    {
        tree[node].preffix = tree[node].suffix = tree[node].sum = tree[node].best = arr[idx] = val;
    }
    else
    {
        int mid = (i + j) / 2;
    
        if (idx <= mid)
            update_tree(2*node, i, mid, idx, val);
        else
            update_tree(2*node+1, mid+1, j, idx, val);
    
        tree[node] = merge(tree[node*2], tree[node*2+1]);
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
        std::scanf("%d%d%d", &a, &l, &r);
        
        if (a == 1)
        {
            auto res = query_tree(1, 0, n-1, l-1, r-1);
            std::printf("%d\n", res.best);
        }
        else
        {
            update_tree(1, 0, n-1, l-1, r);
        }
    }
    
    return 0;
}
