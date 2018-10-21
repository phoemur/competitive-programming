/*KGSS - Maximum Sum
#tree

You are given a sequence A[1], A[2], ..., A[N] ( 0 ≤ A[i] ≤ 10^8 , 2 ≤ N ≤ 10^5 ). There are two types of operations and they are defined as follows:

Update:

This will be indicated in the input by a 'U' followed by space and then two integers i and x.

U i x, 1 ≤ i ≤ N, and x, 0 ≤ x ≤ 10^8.

This operation sets the value of A[i] to x.
Query:

This will be indicated in the input by a 'Q' followed by a single space and then two integers i and j.

Q x y, 1 ≤ x < y ≤ N.

You must find i and j such that x ≤ i, j ≤ y and i != j, such that the sum A[i]+A[j] is maximized. Print the sum A[i]+A[j].
Input

The first line of input consists of an integer N representing the length of the sequence. Next line consists of N space separated integers A[i]. Next line contains an integer Q, Q ≤ 10^5, representing the number of operations. Next Q lines contain the operations.
Output

Output the maximum sum mentioned above, in a separate line, for each Query.
Example

Input:
5
1 2 3 4 5
6
Q 2 4
Q 2 5
U 1 6
Q 1 5
U 1 7
Q 1 5

Output:
7
9
11
12

Warning: large Input/Output data, be careful with certain languages
*/

#include <algorithm>
#include <iostream>

struct Node {
    int maxval;
    int nextmax;
};

int arr[100001];
Node tree[100001 * 3];

void build_tree(int node, int a, int b)
{
    if (a == b)
    {
        tree[node].maxval = arr[a];
        tree[node].nextmax = 0;
    }
    else
    {
        int mid = (a + b) / 2;
        
        build_tree(node*2, a, mid);
        build_tree(node*2+1, mid+1, b);
        
        // merge
        tree[node].maxval  = std::max(tree[node*2].maxval, tree[node*2+1].maxval);
        tree[node].nextmax = std::max({tree[node*2].nextmax, 
                                       tree[node*2+1].nextmax, 
                                       std::min(tree[node*2].maxval, 
                                                tree[node*2+1].maxval)});
    }
}

Node query_tree(int node, int a, int b, int i, int j)
{
    if(a >= i && b <= j) // Current segment is totally within range [i, j]
		return tree[node];
    else
    {
        int mid = (a + b) / 2;
        
        if (i > mid)
            return query_tree(2*node+1, mid+1, b, i, j);
        else if (j <= mid)
            return query_tree(2*node, a, mid, i, j);
        else
        {
            Node res {};
            
            auto left  = query_tree(2*node, a, mid, i, j);
            auto right = query_tree(2*node+1, mid+1, b, i, j);
            
            //merge
            res.maxval  = std::max(left.maxval, right.maxval);
            res.nextmax = std::max({left.nextmax, right.nextmax, std::min(left.maxval, right.maxval)});
            
            return res;
        }
    }
}

// point update
void update_tree(int node, int a, int b, int idx, int val)
{
    if (a == idx && b == idx) // Leaf node
    {
        arr[idx] = val;
        tree[node].maxval = val;
        tree[node].nextmax = 0;
    }
    else
    {
        int mid = (a + b) / 2;
        
        if (mid < idx)
            update_tree(node*2+1, mid+1, b, idx, val);
        else
            update_tree(node*2, a, mid, idx, val);
        
        // merge
        tree[node].maxval  = std::max(tree[node*2].maxval, tree[node*2+1].maxval);
        tree[node].nextmax = std::max({tree[node*2].nextmax, 
                                       tree[node*2+1].nextmax, 
                                       std::min(tree[node*2].maxval, 
                                                tree[node*2+1].maxval)});
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int n;
    std::cin >> n;
    
    for (int i = 0; i < n; ++i)
        std::cin >> arr[i];
    
    build_tree(1, 0, n-1);

    int queries;
    std::cin >> queries;
    
    while (queries--)
    {
        char c;
        int l, r;
        std::cin >> c >> l >> r;
        
        if (c == 'Q')
        {
            auto res = query_tree(1, 0, n-1, l-1, r-1);
            std::cout << res.maxval + res.nextmax << std::endl;
        }
        else
        {
            update_tree(1, 0, n-1, l-1, r);
        }
    }
    
    return 0;
}
