/*Indian National Olympiad in Informatics 2012

You are given a table with 2 rows and N columns. Each cell has an integer in it. The score of such a table is defined as follows: for each column, consider the sum of the two numbers in the column; the maximum of the N numbers so obtained is the score. For example, for the table

7162
1234
 

the score is max(7 + 1, 1 + 2, 6 + 3, 2 + 4) = 9.


The first row of the table is fixed, and given as input. N possible ways to fill the second row are considered:

1,2,...,N
2,3,...,N,1
3,4,...,N,1,2
···
N, 1, ... , ,N − 1
 

For instance, for the example above, we would consider each of the following as possibilities for the second row.

1234
2341
3412
4123
 

Your task is to find the score for each of the above choices of the second row. In the example above, you would evaluate the following four tables,

 7162 7162 7162 7162
 1234 2341 3412 4123
 

and compute scores 9, 10, 10 and 11, respectively.
Input format

The first line of the input has a single integer, N. The second line of the input has N integers, representing the first row, from left to right.
Output format

The output should consist of a single line with N integers. For 1 ² k ² N, the kth number in the output should be the score when the second row of the table is taken to be k,k+1,...,N,1,...,k−1.
Test Data

The testdata is grouped into two subtasks with the following constraints on the inputs.

• Subtask 1 [30 points] : 1 ≤ N ≤ 3000.

• Subtask 2 [70 points] : 1 ≤ N ≤ 200000.

In both the subtasks, all the integers in the first row of the table are between 1 and 100000, inclusive.
Example

Here is the sample input and output corresponding to the example above.
Sample input

4
7 1 6 2

Sample output

9 10 10 11
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

int tree[600006]; // Segment Tree
int lazy[600006]; // Lazy propagation Array

// Build segment tree for range max queries
void build(int node, int lo, int hi, const std::vector<int>& vec)
{
    if (lo > hi)
        return;
    else if (lo == hi)
        tree[node] = vec[lo];
    else
    {
        int mid = (lo + hi) / 2;
        
        build(node*2,      lo, mid, vec);
        build(node*2+1, mid+1,  hi, vec);
        
        tree[node] = std::max(tree[node*2], tree[node*2+1]);
    }
}

// Propagate updates lazily down the tree
inline void push_down(int node, int a, int b)
{
    if(lazy[node] != 0)
    {
        tree[node] += lazy[node];
        
        if (a != b)
        {
            lazy[node*2]   += lazy[node];
            lazy[node*2+1] += lazy[node];
        }
        
        lazy[node] = 0;
    }
}

// Increment all elements from [i,j] inclusive with val
void range_update(int node, int lo, int hi, int i, int j, int val)
{
    push_down(node, lo, hi);
    
    if (lo > hi || lo > j || hi < i)
        return;
    else if (lo >= i && hi <= j)
    {
        // Update lazily
        tree[node] += val;
        
        if (lo != hi)
        {
            lazy[node*2]   += val;
            lazy[node*2+1] += val;
        }    
    }
    else
    {
        int mid = (lo + hi) / 2;
        
        range_update(node*2,      lo, mid, i, j, val);
        range_update(node*2+1, mid+1,  hi, i, j, val);
        
        tree[node] = std::max(tree[node*2], tree[node*2+1]);
    }
}

int main()
{   
    std::memset(tree, 0, sizeof(int) * 600006);
    std::memset(lazy, 0, sizeof(int) * 600006);
    
    int n;
    std::scanf("%d", &n);
    
    std::vector<int> vec (n);
    
    for (int i = 1; i <= n; ++i)
    {
        std::scanf("%d", &vec[i-1]);
        vec[i-1] += i;
    }
    
    build(1, 0, n-1, vec);
    
    std::printf("%d", tree[1]);
    if (n == 1) std::printf("\n");
    
    for (int i = 1; i < n; ++i)
    {
        range_update(1, 0, n-1, 0, n-1, 1); // Add 1 to every vec[idx]
        range_update(1, 0, n-1, n-i, n-i, -1 * n); // vec[n-i] -= n
        push_down(1, 0, n-1);
        
        std::printf(" %d", tree[1]);
        
        if (i == n-1) std::printf("\n");
    }
    
    return 0;
}
