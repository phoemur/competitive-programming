/*LITE - Light Switching
#tree


Farmer John tries to keep the cows sharp by letting them play with intellectual toys. One of the larger toys is the lights in the barn.  Each of the N (2 <= N <= 100,000) cow stalls conveniently numbered 1..N has a colorful light above it.

At the beginning of the evening, all the lights are off. The cows control the lights with a set of N pushbutton switches that toggle the lights; pushing switch i changes the state of light i from off to on or from on to off.

The cows read and execute a list of M (1 <= M <= 100,000) operations expressed as one of two integers (0 <= operation <= 1).

The first kind of operation (denoted by a 0 command) includes two subsequent integers S_i and E_i (1 <= S_i <= E_i <= N) that indicate a starting switch and ending switch. They execute the operation by pushing each pushbutton from S_i through E_i inclusive exactly once.

The second kind of operation (denoted by a 1 command) asks the cows to count how many lights are on in the range given by two integers S_i and E_i (1 <= S_i <= E_i <= N) which specify the inclusive range in which the cows should count the number of lights that are on.

Help FJ ensure the cows are getting the correct answer by processing the list and producing the proper counts.
Input


Line 1: Two space-separated integers: N and M
Lines 2..M+1: Each line represents an operation with three space-separated integers: operation, S_i, and E_i
Output

Lines 1..number of queries: For each output query, print the count as an integer by itself on a single line.
Example

Input:
4 5
0 1 2
0 2 4
1 2 3
0 2 4
1 1 4

Output:
1
2*/

#include <cstdio>
#include <cstring>

int arr[100005];
long tree[100005 * 3];
bool lazy[100005 * 3];

void update_tree(int node, int a, int b, int i, int j)
{
    // Propagate updates if necessary
    if(lazy[node] == true)
    {
        tree[node] = b - a + 1 - tree[node]; //total lights minus already switched on
        lazy[node] = false;
        
        if(a != b)
        {
            // lazy propagate
            lazy[2*node] = lazy[2*node] ? false: true;
            lazy[2*node+1] = lazy[2*node+1] ? false: true;
        }
    }

    if(a > b || a > j || b < i) // no overlap
        return;

    if(a >= i && b <= j) // total overlap
    {
        tree[node] = b - a + 1 - tree[node];
        
        if(a != b)
        {
            // lazy propagate
            lazy[2*node] = lazy[2*node] ? false: true;
            lazy[2*node+1] = lazy[2*node+1] ? false: true;
        }
        
        return;
    }
    
    int mid = (a + b) / 2;
    update_tree(node*2,a,mid,i,j);
    update_tree(node*2+1,mid+1,b,i,j);
    
    tree[node] = tree[node*2] + tree[node*2+1];
}

long query_tree(int node, int a, int b, int i, int j)
{
    // Propagate updates if necessary
    if(lazy[node] == true)
    {
        tree[node] = b - a + 1 - tree[node]; //total lights minus already switched on
        lazy[node] = false;
        
        if(a != b)
        {
            // lazy propagate
            lazy[2*node] = lazy[2*node] ? false: true;
            lazy[2*node+1] = lazy[2*node+1] ? false: true;
        }
    }    
    
    if(a > b || a > j || b < i) // no overlap
        return 0; 
    else if(a >= i && b <= j) // total overlap
        return tree[node];
    else
    {
        // partial overlap
        int mid = (a + b) / 2;
    
        int left  = query_tree(node*2, a, mid, i, j);
        int right = query_tree(node*2+1, mid + 1, b, i, j);
    
        return left + right;
    }
}

int main()
{
    std::memset(arr,  0, sizeof(int) * 100005);
    std::memset(tree, 0, sizeof(long) * 3 * 100005);
    std::memset(lazy, 0, sizeof(bool) * 3 * 100005);
    
    int n, m;
    std::scanf("%d %d", &n, &m);
    
    while (m--)
    {
        int a, l, r;
        std::scanf("%d %d %d", &a, &l, &r);

        if (a == 0)
        {
            update_tree(1, 0, n-1, l-1, r-1);
        }
        else
        {
            std::printf("%ld\n", query_tree(1, 0, n-1, l-1, r-1));
        }
    }
    
    
    return 0;
}
