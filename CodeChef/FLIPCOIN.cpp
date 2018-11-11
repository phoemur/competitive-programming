/*All submissions for this problem are available.

There are N coins kept on the table, numbered from 0 to N - 1. Initially, each coin is kept tails up. You have to perform two types of operations:

1) Flip all coins numbered between A and B inclusive. This is represented by the command "0 A B"

2) Answer how many coins numbered between A and B inclusive are heads up. This is represented by the command "1 A B".

Input :

The first line contains two integers, N and Q. Each of the next Q lines are either of the form "0 A B" or "1 A B" as mentioned above.

Output :

Output 1 line for each of the queries of the form "1 A B" containing the required answer for the corresponding query.

Sample Input :
4 7
1 0 3
0 1 2
1 0 1
1 0 0
0 0 3
1 0 3 
1 3 3

Sample Output :
0
1
0
2
1

Constraints :
1 <= N <= 100000
1 <= Q <= 100000
0 <= A <= B <= N - 1
*/

#include <algorithm>
#include <cstdio>
#include <cstring>

struct Node {
    int tails;
    int heads;
};

Node tree[300003]; // Segment Tree
int  lazy[300003]; // Lazy Propagation array

// Merge Function
Node operator+(const Node& a, const Node& b)
{
    return {a.tails + b.tails, a.heads + b.heads};
}

// Build the empty tree
void build_tree(int node, int lo, int hi)
{
    if (lo > hi)
        return;
    else if (lo == hi) // Leaf node
    {
        tree[node].tails = 1;
        tree[node].heads = 0;
    }
    else // Internal Node
    {
        auto mid = (lo + hi) / 2;
        
        build_tree(node*2,      lo, mid);
        build_tree(node*2+1, mid+1,  hi);
        
        tree[node] = tree[node*2] + tree[node*2+1];
    }
}

// Propagate updates lazily down the tree
inline void push_down(int node, int lo, int hi)
{
    if (lazy[node] != 0)
    {
        // If lazy[node] is odd than flip the counts
        if (lazy[node] & 1)
            std::swap(tree[node].heads, tree[node].tails);
        
        if (lo != hi) // Propagate if not leaf
        {
            lazy[node*2]   += lazy[node];
            lazy[node*2+1] += lazy[node];
        }
        
        lazy[node] = 0; // Reset node
    }
}

// Range update function -> flip coins between [i,j] inclusive
void range_update(int node, int lo, int hi, int i, int j)
{
    push_down(node, lo, hi);
    
    if (lo > hi || lo > j || hi < i)
        return;
    else if (lo >= i && hi <= j) // Update lazily
    {
        std::swap(tree[node].heads, tree[node].tails);
        
        if (lo != hi) // Internal node -> propagate
        {
            lazy[node*2]++;
            lazy[node*2+1]++;
        }
    }
    else
    {
        auto mid = (lo + hi) / 2;
        
        range_update(node*2,      lo, mid, i, j);
        range_update(node*2+1, mid+1,  hi, i, j);
        
        tree[node] = tree[node*2] + tree[node*2+1];
    }
}

// Query between indexes [i, j] inclusive
Node range_query(int node, int lo, int hi, int i, int j)
{
    push_down(node, lo, hi);
    
    if (lo > hi || lo > j || hi < i) // No overlap
        return {0, 0};
    else if (lo >= i && hi <= j) // Total overlap
        return tree[node];
    else // Partial overlap
    {
        auto mid = (lo + hi) / 2;
        
        auto left  = range_query(node*2,      lo, mid, i, j);
        auto right = range_query(node*2+1, mid+1,  hi, i, j);
        
        return left + right;
    }
}

int main()
{
    int n, q;
    std::scanf("%d %d", &n, &q);
    
    build_tree(1, 0, n-1);
    std::memset(lazy, 0, sizeof(int) * 300003);
    
    while (q--)
    {
        int op, l, r;
        std::scanf("%d %d %d", &op, &l, &r);
        
        if (op == 1) // Query
        {
            auto res = range_query(1, 0, n-1, l, r);
            std::printf("%d\n", res.heads);
        }
        else // Flip
        {
            range_update(1, 0, n-1, l, r);
        }
    }
    
    return 0;
}
