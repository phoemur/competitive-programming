/*SALMAN - Salary Management
#tree #dfs

Salary Management

You are working as a software engineer of Moogle! Now the boss of Moogle wants you to create a program which will efficiently handle some operations. At first, we should tell you about the structure of the employees at Moogle! Each employee has an integer id from 1 to N. Where 1 is the id of the Managing Director of Moogle! , who is the greatest boss of all the employees. Then except the Managing Director, each employee has an immediate boss. No employees have more than one immediate boss. Now your boss wants to have some operation like this –

    He will give you an ID of an employee; you need to find the sum of salary of all the employees under that employee including him/herself.
    He will give you an ID of an employee; you need to increase the salary of all the employees under that employee including him/herself by the minimum of minimum salary of all the employees under that employee including him/her and 1000.

Let’s see the structure, hope you will get a clear idea about the problem.

  Employee Hiearchy

Employee Hierarchy

Salary Table:

ID
	

1
	

2
	

3
	

4
	

5
	

6
	

7

Salary (BDT)
	

500
	

300
	

200
	

100
	

10
	

200
	

100


Now if your boss wants to do the first operation for Employee ID 2. Then the output will be

300+100+200= 600 BDT

If your boss wants to do the second operation for the Employee ID 1, then the salary table becomes -

ID
	

1
	

2
	

3
	

4
	

5
	

6
	

7

Salary (BDT)
	

510
	

310
	

210
	

110
	

20
	

210
	

110


As minimum salary is 10 for Employee id 5 and which is less than 1000.

Input

Input starts with an integer T (≤ 3), denoting the number of test cases.

The first line of a case is a blank line. The next line contains two integers N (1 ≤ N ≤ 105), q (1 ≤ q ≤ 50000) where N denotes the number of nodes and q denotes the number of queries. The nodes are numbered from 1 to N.

Then there will be N lines. The ith (1 ≤ i ≤ N) line contains two integers pi and si (0 ≤ pi ≤  N, 1 ≤ si < 500). pi denotes the parent and si denotes the salary of the ith employee, respectively. You can assume that the employee id with 1 is the managing director and only its parent is 0.

Each of the next q lines contains a query. Each query contains two integers: c and v (1 ≤ c ≤ 2, 1 ≤ v ≤ N), where c denotes operation type, and v denotes the employee id. If the c = 1, then it means to do the first operation. If c=2, then the second operation.

You can assume that the input builds a valid rooted tree.

Output

For each case, print the case number in a line. Then for each query type 1, print the sum of the salary.


Sample Input
	

Output for Sample Input

1


7 3

0 500

1 300

1 200

1 100

3 10

2 200

2 100

1 2

2 1

1 2
	

Case 1:

600

630

Note

Dataset is huge. Use faster I/O methods.



Problem Setter: Ahmad Faiyaz

Special Thanks: Syed Shahriar Manjur
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <limits>
#include <vector>

#define N 100001 

std::vector<int> adj[N]; // Tree adjacency List
int           salary[N]; // Salary of each employee
int           seg_id[N]; // Map node number to index in the segtree
int         start_id[N]; // Leftmost child
int           end_id[N]; // Rightmost child (all seg_ids on a subtree are consecutive so we can query the array)

long long min_segtree[3*N]; // Segtree for RMQ
long long sum_segtree[3*N]; // Segtree for range sum query
long long        lazy[3*N]; // Lazy Propagation array (for both segtrees)

int pos;

inline void cleanup(int n)
{
    for (int i = 0; i < n; ++i)
        adj[i].clear();

    pos = 0;
    
    std::memset(lazy, 0, sizeof(long long) * 3 * n);
}

/* This DFS function is used to map every subtree to a consecutive array interval.
 * We need this to perform queries on the segment trees.
 *  - node[i] will be stored at segtree[seg_id[i]].
 *  - the subtree node[i] will correspond to the interval [start_id[i], end_id[i]],
 *    which will contain all the nodes below it */
void DFS(int node)
{    
    seg_id[pos] = node;
    start_id[node] = pos;
    
    for (auto& child: adj[node])
    {
        ++pos;
        DFS(child);
    }
    
    end_id[node] = pos;
}

// Build both SegTrees
void build_all(int node, int lo, int hi)
{
    if (lo > hi)
        return;
    else if (lo == hi)
    {
        min_segtree[node] = salary[seg_id[lo]];
        sum_segtree[node] = salary[seg_id[lo]];
    }
    else
    {
        int mid = (lo + hi) / 2;
        
        build_all(node*2,      lo, mid);
        build_all(node*2+1, mid+1,  hi);
        
        min_segtree[node] = std::min(min_segtree[node*2], min_segtree[node*2+1]);
        sum_segtree[node] = sum_segtree[node*2] + sum_segtree[node*2+1];
    }
}

// Propagate updates down the trees (both)
inline void push_down(int node, int a, int b)
{
    if(lazy[node] != 0)
    {
        sum_segtree[node] += lazy[node] * (b - a + 1);
        min_segtree[node] += lazy[node];
        
        if(a != b)
        {
             lazy[node*2]   += lazy[node];
             lazy[node*2+1] += lazy[node];
        }
        
        lazy[node] = 0;
    }
}


long long sum_range_query(int node, int lo, int hi, int i, int j)
{
    push_down(node, lo, hi);
    
    if (lo > hi || lo > j || hi < i)
        return 0;
    else if (lo >= i && hi <= j)
        return sum_segtree[node];
    else
    {
        int mid = (lo + hi) / 2;
        
        long long q1 = sum_range_query(node*2,      lo, mid, i, j);
        long long q2 = sum_range_query(node*2+1, mid+1,  hi, i, j);
        
        return q1 + q2;
    }
}

long long min_range_query(int node, int lo, int hi, int i, int j)
{
    push_down(node, lo, hi);
    
    if (lo > hi || lo > j || hi < i)
        return std::numeric_limits<int>::max();
    else if (lo >= i && hi <= j)
        return min_segtree[node];
    else
    {
        int mid = (lo + hi) / 2;
        
        long long q1 = min_range_query(node*2,      lo, mid, i, j);
        long long q2 = min_range_query(node*2+1, mid+1,  hi, i, j);
        
        return std::min(q1, q2);
    }
}

void range_update(int node, int a, int b, int i, int j, long long val)
{
    push_down(node, a, b);

    int mid = (a + b) / 2;
    
    if(a > b || a > j || b < i)
        return;
    else if(a >= i && b <= j)
    {
        // Update lazily
        sum_segtree[node] += val * (b - a + 1);
        min_segtree[node] += val;
        
        if (a != b)
        {
            lazy[node*2]   += val;
            lazy[node*2+1] += val;
        }
    }
    else
    {
        range_update(node*2, a, mid, i, j, val);
        range_update(node*2+1, mid+1, b, i, j, val);
        
        sum_segtree[node] = sum_segtree[node*2] + sum_segtree[node*2+1];
        min_segtree[node] = std::min(min_segtree[node*2], min_segtree[node*2+1]);
    }
}

int main()
{
    int tests;
    std::scanf("%d", &tests);
    
    for (int cas = 1; cas <= tests; ++cas)
    {
        int n, q;
        std::scanf("%d %d", &n, &q);
        
        cleanup(n);
        
        // Input
        for (int i = 0; i < n; ++i)
        {
            int par;
            std::scanf("%d %ld", &par, &salary[i]);
            --par; // Will use 0 based indexing
            
            if (par >= 0)
                adj[par].push_back(i);
        }
        
        // Preprocess
        DFS(0);
        build_all(1, 0, n-1);
        
        // Queries
        std::printf("Case %d:\n", cas);
        while (q--)
        {
            int op, v;
            std::scanf("%d %d", &op, &v);
            --v;
            
            auto bg = start_id[v];
            auto ed = end_id[v];
            
            if (op == 1)
            {
                auto res = sum_range_query(1, 0, n-1, bg, ed);
                std::printf("%lld\n", res);
            }
            else // op == 2
            {
                auto mn = min_range_query(1, 0, n-1, bg, ed);
                mn = std::min(mn, 1000LL);
                
                range_update(1, 0, n-1, bg, ed, mn);
            }
        }
    }
    
    return 0;
}
