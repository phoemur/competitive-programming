/*GSS4 - Can you answer these queries IV
#tree

You are given a sequence A of N(N <= 100,000) positive integers. There sum will be less than 1018. On this sequence you have to apply M (M <= 100,000) operations:

(A) For given x,y, for each elements between the x-th and the y-th ones (inclusively, counting from 1), modify it to its positive square root (rounded down to the nearest integer).

(B) For given x,y, query the sum of all the elements between the x-th and the y-th ones (inclusively, counting from 1) in the sequence.
Input

Multiple test cases, please proceed them one by one. Input terminates by EOF.

For each test case:

The first line contains an integer N. The following line contains N integers, representing the sequence A1..AN.
The third line contains an integer M. The next M lines contain the operations in the form "i x y".i=0 denotes the modify operation, i=1 denotes the query operation.
Output

For each test case:

Output the case number (counting from 1) in the first line of output. Then for each query, print an integer as the problem required.

Print an blank line after each test case.

See the sample output for more details.
Example

Input:
5
1 2 3 4 5
5
1 2 4
0 2 4
1 2 4
0 4 5
1 1 5
4
10 10 10 10
3
1 1 4
0 2 3
1 1 4

Output:
Case #1:
9
4
6

Case #2:
40
26

*/

#include <algorithm>
#include <cmath>
#include <cstdio>

long arr[100005];
long tree[100005 * 3];
bool update[100005 * 3]; // Prunning the updates 

void build_tree(int node, int a, int b)
{
    if (a == b)
    {
        tree[node] = arr[a];
        if (arr[a] == 1) // Do not need to update further
            update[node] = false;
        else
            update[node] = true;
    }
    else
    {
        int mid = (a + b) / 2;
        
        build_tree(node*2, a, mid);
        build_tree(node*2+1, mid+1, b);
        
        tree[node] = tree[node*2] + tree[node*2+1];
        update[node] = update[node*2] || update[node*2+1];
    }
}

void update_tree(int node, int a, int b, int i, int j)
{
    if(a > b || a > j || b < i)
        return;
    else if (a == b)
    {
        tree[node] = arr[a] = static_cast<long>(std::floor(std::sqrt(arr[a])));
        if (tree[node] == 1) // Do not need to update further
            update[node] = false;
        else
            update[node] = true;
    }
    else
    {
        int mid = (a + b) / 2;
        
        if (a > mid)
            update_tree(node*2+1, mid+1, b, i, j);
        else if (b <= mid)
            update_tree(node*2, a, mid, i, j);
        else if (update[node] == false) // Do not need to update further
            return;
        else
        {
            update_tree(node*2,a,mid,i,j);
            update_tree(node*2+1,mid+1,b,i,j);
            
            tree[node] = tree[node*2] + tree[node*2+1];
            update[node] = update[node*2] || update[node*2+1];
        }
    }  
}

long query(int node, int a, int b, int i, int j)
{
    if(a>b || a>j || b<i)
        return 0;    
    else if(a>=i && b <= j)
        return tree[node];
    else
    {
        int mid = (a + b) / 2;
        long q1 = query(node*2,a,mid,i,j);
        long q2 = query(node*2+1,mid+1,b,i,j);

        return q1 + q2;
    }
}

int main()
{
    int n, test = 1;
    
    while (std::scanf("%d", &n) != EOF)
    {
        for (int i = 0; i < n; ++i)
        {
            std::scanf("%ld", &arr[i]);
        }
        
        build_tree(1, 0, n-1);
        
        int m;
        std::scanf("%d", &m);
        
        std::printf("Case #%d:\n", test++);
        while(m--)
        {
            int oper, l, r;
            std::scanf("%d %d %d", &oper, &l, &r);
            
            if (oper == 1)
            {
                std::printf("%ld\n", query(1, 0, n-1, std::min(l-1, r-1), std::max(l-1, r-1)));
            }
            else
            {
                update_tree(1, 0, n-1, std::min(l-1, r-1), std::max(l-1, r-1));
            }
        }
    }
    
    return 0;
}
