/*GSS1 - Can you answer these queries I
#tree

You are given a sequence A[1], A[2], ..., A[N] . ( |A[i]| ≤ 15007 , 1 ≤ N ≤ 50000 ). A query is defined as follows:
Query(x,y) = Max { a[i]+a[i+1]+...+a[j] ; x ≤ i ≤ j ≤ y }.
Given M queries, your program must output the results of these queries.
Input

    The first line of the input file contains the integer N.
    In the second line, N numbers follow.
    The third line contains the integer M.
    M lines follow, where line i contains 2 numbers xi and yi.

Output

Your program should output the results of the M queries, one query per line.
Example

Input:
3 
-1 2 3
1
1 2

Output:
2

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
        int l, r;
        std::scanf("%d%d", &l, &r);
        
        auto res = query_tree(1, 0, n-1, l-1, r-1);
        
        std::printf("%d\n", res.best);
    }
    
    return 0;
}
