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

#include <cstdio>
#include <cstdint>
#include <cstring>
#include <limits>
#include <stack>
#include <tuple>

std::int64_t tree[4000001];
std::int64_t lazy[4000001];

constexpr static int INF = std::numeric_limits<int>::max();

using QueryAdaptor = std::tuple<std::int64_t, std::int64_t, std::int64_t>; // Tuple<Node, lo, hi>

// Propagate updates lazily down the tree
inline void push_down(std::int64_t node, 
                      std::int64_t a, 
                      std::int64_t b)
{
    if(lazy[node] != 0)
    {
        tree[node] += lazy[node] * (b - a + 1);
        
        if(a != b)
        {
            lazy[2*node]   += lazy[node];
            lazy[2*node+1] += lazy[node];
        }
        
        lazy[node] = 0;
    }
}

// Iterative Range_Update function
void update_tree(std::int64_t node, 
                 std::int64_t a, 
                 std::int64_t b, 
                 std::int64_t i, 
                 std::int64_t j, 
                 std::int64_t val)
{
    std::stack<QueryAdaptor> st;
    
    st.emplace(node, a, b);
    
    while (!st.empty())
    {
        std::int64_t currnode, curra, currb;
        std::tie(currnode, curra, currb) = st.top();
        st.pop();
      
        if (curra == currb && curra == INF) // Node merge flagged
        {
            tree[currnode] = tree[currnode*2] + tree[currnode*2+1];
        }
        else
        {
            push_down(currnode, curra, currb);

            if(curra > currb || curra > j || currb < i) // No overlap
                continue;
            else if(curra >= i && currb <= j) // Total Overlap
            {
                // Update lazily
                tree[currnode] += val * (currb - curra + 1);
        
                if(curra != currb)
                {
                    lazy[currnode*2]   += val;
                    lazy[currnode*2+1] += val;
                }
            }
            else // Partial Overlap
            {
                // Flag this node to be merged postorder
                st.emplace(currnode, INF, INF); 
            
                // Push children
                std::int64_t mid = (curra + currb) / 2;
                
                st.emplace(currnode*2,   curra,   mid);
                st.emplace(currnode*2+1, mid+1, currb);
            }
        }
    }
}


std::int64_t query(std::int64_t node, 
                   std::int64_t a, 
                   std::int64_t b, 
                   std::int64_t i, 
                   std::int64_t j)
{
    std::stack<QueryAdaptor> st; // For Iterative Preorder Traversal using stack
    
    st.emplace(node, a, b);
    std::int64_t result = 0;
    
    while (!st.empty())
    {
        std::int64_t currnode, curra, currb;
        std::tie(currnode, curra, currb) = st.top();
        st.pop();
      
        push_down(currnode, curra, currb);
        
        if(curra > currb || curra > j || currb < i)
            continue;        
        else if(curra >= i && currb <= j)
            result += tree[currnode];
        else
        {
            std::int64_t mid = (curra + currb) / 2;
            
            st.emplace(currnode * 2,     curra,   mid);
            st.emplace(currnode * 2 + 1, mid+1, currb);
        }
    }
    
    return result;
}

int main()
{   
    int tests;
    std::scanf("%d", &tests);
    
    while (tests--)
    {
        long long n, c;
        std::scanf("%lld%lld", &n, &c);
        
        std::memset(tree, 0, sizeof(std::int64_t) * 4000001);
        std::memset(lazy, 0, sizeof(std::int64_t) * 4000001);
        
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
