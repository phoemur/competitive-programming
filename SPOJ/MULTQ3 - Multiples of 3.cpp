/*MULTQ3 - Multiples of 3
#tree

There are N numbers a[0],a[1]..a[N - 1]. Initally all are 0. You have to perform two types of operations :

1) Increase the numbers between indices A and B (inclusive) by 1. This is represented by the command "0 A B"
2) Answer how many numbers between indices A and B (inclusive) are divisible by 3. This is represented by the command "1 A B".
Input

The first line contains two integers, N and Q. Each of the next Q lines are either of the form "0 A B" or "1 A B" as mentioned above.
Output

Output 1 line for each of the queries of the form "1 A B" containing the required answer for the corresponding query.
Sample

Sample Input :
4 7
1 0 3
0 1 2
0 1 3
1 0 0
0 0 3
1 3 3
1 0 3

Sample Output :
4
1
0
2

Constraints

1 <= N <= 100000
1 <= Q <= 100000
0 <= A <= B <= N - 1
*/

#include <cstdio>
#include <cstring>

// Segment tree Node
struct Node {
    int cnt[3]; // Count of num % 3 in range
    
    int&       operator[](std::size_t i)       {return cnt[i];}
    const int& operator[](std::size_t i) const {return cnt[i];}
};

Node tree[300003]; // Segment tree
int  lazy[300003]; // Lazy Propagation array

// Node Merge Function
Node operator+(const Node& lhs, const Node& rhs)
{
    Node res;
    
    res[0] = lhs[0] + rhs[0];
    res[1] = lhs[1] + rhs[1];
    res[2] = lhs[2] + rhs[2];
    
    return res;
}

// Build the empty Segment tree
void build_tree(int node, int a, int b)
{
    if (a > b) // Impossible
        return;
    else if (a == b) // Leaf Node
    {
        tree[node][0] = 1; // 0 is divisible by 3
        tree[node][1] = 0;
        tree[node][2] = 0;
    }
    else
    {
        // Divide
        int mid = (a + b) / 2;
        
        build_tree(node*2,       a, mid);
        build_tree(node*2+1, mid+1,   b);
        
        // Conquer (merge)
        tree[node] = tree[node*2] + tree[node*2+1];
    }
}

// Right rotate tree[node] by offset
inline void right_rotate(int node, int offset)
{
    while (offset--)
    {
        int tmp = tree[node][2];
        tree[node][2] = tree[node][1];
        tree[node][1] = tree[node][0];
        tree[node][0] = tmp;
    }
}

// Propagate updates lazily down the tree
inline void push_down(int node, int a, int b)
{
    if(lazy[node] != 0)
    {
        // Right rotate by lazy[node] factor
        right_rotate(node, lazy[node] % 3);
        
        if (a != b)
        {
            lazy[node*2]   += lazy[node];
            lazy[node*2+1] += lazy[node];
        }
        
        lazy[node] = 0;
    }
}

// Range Query the segment tree
Node query(int node, int a, int b, int i, int j)
{
    push_down(node, a, b);
    
    if(a > b || a > j || b < i) // No overlap
        return Node();
    else if(a >= i && b <= j) // Total overlap
        return tree[node];
    else // Partial overlap
    {
        int mid = (a + b) / 2;
        Node q1 = query(node*2,       a, mid, i, j);
        Node q2 = query(node*2+1, mid+1,   b, i, j);

        return q1 + q2;
    }
}

// Range update with lazy propagation
void update(int node, int a, int b, int i, int j)
{
    push_down(node, a, b);
    
    if (a > b || a > j || b < i)
        return;
    else if (a >= i && b <= j)
    {
        // Update lazily (Right rotate tree[node] 1 position)
        right_rotate(node, 1);
        
        if (a != b)
        {
            lazy[node*2]++;
            lazy[node*2+1]++;
        }
    }
    else
    {
        int mid = (a + b) / 2;
        
        update(node*2,       a, mid, i, j);
        update(node*2+1, mid+1,   b, i, j);
        
        tree[node] = tree[node*2] + tree[node*2+1];
    }
}


int main()
{
    std::memset(lazy, 0, sizeof(int)  * 300003);
    
    int n, q;
    std::scanf("%d %d", &n, &q);
    
    build_tree(1, 0, n-1);
    
    while (q--)
    {
        int op, l, r;
        std::scanf("%d %d %d", &op, &l, &r);
        
        if (op == 1)
        {
            Node res = query(1, 0, n-1, l, r);
            std::printf("%d\n", res[0]);
        }
        else
        {
            update(1, 0, n-1, l, r);
        }
    }
    
    return 0;
}
