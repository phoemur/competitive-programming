/*GSS5 - Can you answer these queries V
#tree

You are given a sequence A[1], A[2], ..., A[N] . ( |A[i]| <= 10000 , 1 <= N <= 10000 ). A query is defined as follows: Query(x1,y1,x2,y2) = Max { A[i]+A[i+1]+...+A[j] ; x1 <= i <= y1 , x2 <= j <= y2 and x1 <= x2 , y1 <= y2 }. Given M queries (1 <= M <= 10000), your program must output the results of these queries.
Input

The first line of the input consist of the number of tests cases <= 5. Each case consist of the integer N and the sequence A. Then the integer M. M lines follow, contains 4 numbers x1, y1, x2 y2.
Output

Your program should output the results of the M queries for each test case, one query per line.
Example

Input:
2
6 3 -2 1 -4 5 2
2
1 1 2 3
1 3 2 5
1 1
1
1 1 1 1

Output:
2
3
1


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

int   arr[1 << 14];
Node tree[1 << 15];

inline Node merge(const Node& left, const Node& right)
{
    Node res {};
        
    res.sum     = left.sum + right.sum;
    res.preffix = maximum(left.preffix, left.sum + right.preffix);
    res.suffix  = maximum(right.suffix, right.sum + left.suffix);
    res.best    = maximum(left.best, 
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
    if (a > b || a > j || b < i)
        return Node{};
    else if(a>=i && b<=j)
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
    int tests;
    std::scanf("%d", &tests);
    
    while (tests--)
    {
        int n;
        std::scanf("%d", &n);
        
        for (int i = 0; i < n; ++i)
            std::scanf("%d", &arr[i]);
        
        build_tree(1, 0, n-1);
        
        int queries;
        std::scanf("%d", &queries);
        
        while (queries--)
        {
            int x1, y1, x2, y2, res = 0;
            std::scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            --x1; --y1; --x2; --y2; // zero based index used
            
            if (y1 < x2) // No overlap
            {
                res  = query_tree(1, 0, n-1, y1+1, x2-1).sum;
                res += query_tree(1, 0, n-1,   x2,   y2).preffix;
                res += query_tree(1, 0, n-1,   x1,   y1).suffix;
            }
            else // Overlap
            {
                res = maximum(query_tree(1, 0, n-1, x2, y1).best, 
                              query_tree(1, 0, n-1, x1, x2-1).suffix + query_tree(1, 0, n-1,   x2, y2).preffix, 
                              query_tree(1, 0, n-1, x1,   y1).suffix + query_tree(1, 0, n-1, y1+1, y2).preffix);
            }
            
            std::printf("%d\n", res);
        }
    }
    
    return 0;
}
