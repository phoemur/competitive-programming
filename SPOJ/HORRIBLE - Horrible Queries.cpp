/*HORRIBLE - Horrible Queries
#tree #binary-search

World is getting more evil and it's getting tougher to get into the Evil League of Evil. Since the legendary Bad Horse has retired, now you have to correctly answer the evil questions of Dr. Horrible, who has a PhD in horribleness (but not in Computer Science). You are given an array of N elements, which are initially all 0. After that you will be given C commands. They are -

* 0 p q v - you have to add v to all numbers in the range of p to q (inclusive), where p and q are two indexes of the array.

* 1 p q - output a line containing a single integer which is the sum of all the array elements between p and q (inclusive)

 
Input

In the first line you'll be given T, number of test cases.

Each test case will start with N (N <= 100 000) and C (C <= 100 000). After that you'll be given C commands in the format as mentioned above. 1 <= p, q <= N and 1 <= v <= 10^7.
Output

Print the answers of the queries.
Example

Input:
1
8 6
0 2 4 26
0 4 8 80
0 4 5 20
1 8 8 
0 5 7 14
1 4 8

Output:
80
508

*/

#include <cstdint>
#include <cstdio>
#include <cstring>

std::int64_t tree[4000001];
std::int64_t lazy[4000001];

// Propagate updates lazily down the tree
inline void push_down(std::int64_t node, 
                      std::int64_t a, 
                      std::int64_t b)
{
    if(lazy[node] != 0)
    {
        tree[node] += lazy[node];
        
        if(a != b)
        {
            std::int64_t mid = (a + b) / 2;
            
            lazy[2*node]   += (lazy[node]/(b-a+1)) * (mid-a+1);
            lazy[2*node+1] += (lazy[node]/(b-a+1)) *   (b-mid);
        }
        
        lazy[node] = 0;
    }
}

void update_tree(std::int64_t node, 
                 std::int64_t a, 
                 std::int64_t b, 
                 std::int64_t i,
                 std::int64_t j,
                 std::int64_t val)
{
    push_down(node, a, b);

    std::int64_t mid = (a + b) / 2;
    
    if(a>b || a>j || b<i)
        return;
    else if(a >= i && b <= j)
    {
        // Update lazily
        tree[node] += val*(b-a+1);
        
        if(a!=b)
        {
            lazy[node*2]   += val * (mid-a+1);
            lazy[node*2+1] += val *   (b-mid);
        }
    }
    else
    {
        update_tree(node*2, a, mid, i, j, val);
        update_tree(node*2+1, mid+1, b, i, j, val);
        
        tree[node] = tree[node*2] + tree[node*2+1];
    }
}

std::int64_t query(std::int64_t node, std::int64_t a, std::int64_t b, std::int64_t i, std::int64_t j)
{
    push_down(node, a, b);
    
    if(a > b || a > j || b < i) // No overlap
        return 0;
    else if(a >= i && b <= j) // Total overlap
        return tree[node];
    else // Partial overlap
    {
        std::int64_t mid = (a + b) / 2;
        std::int64_t q1 = query(node*2, a, mid, i, j);
        std::int64_t q2 = query(node*2+1, mid+1, b, i, j);

        return q1 + q2;
    }
}

int main()
{   
    int tests;
    std::scanf("%d", &tests);
    
    while (tests--)
    {
        std::memset(tree, 0, sizeof(std::int64_t) * 4000001);
        std::memset(lazy, 0, sizeof(std::int64_t) * 4000001);
        
        long long n, c;
        std::scanf("%lld%lld", &n, &c);
        
        while (c--)
        {
            long long a, l, r, v;
            std::scanf("%lld", &a);
            
            if (a == 0)
            {
                std::scanf("%lld%lld%lld", &l, &r, &v);
                update_tree(1,0,n-1,l-1,r-1,v);
            }
            else
            {                
                std::scanf("%lld%lld", &l, &r);
                std::printf("%lld\n", query(1, 0, n-1, l-1, r-1));
            }
        }
    }
    
    return 0;
}
