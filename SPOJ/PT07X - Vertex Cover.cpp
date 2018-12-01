/*PT07X - Vertex Cover
#tree

You are given an unweighted, undirected tree. Write a program to find a vertex set of minimum size in this tree such that each edge has as least one of its end-points in that set.
Input

The first line of the input file contains one integer N --- number of nodes in the tree (0 < N <= 100000). Next N-1 lines contain N-1 edges of that tree --- Each line contains a pair (u, v) means there is an edge between node u and node v (1 <= u,v <= N).
Output

Print number of nodes in the satisfied vertex set on one line.
Example 1

Input:
3
1 2
1 3

Output:
1

Explanation:
The set can be {1}

Example 2

Input:
3
1 2
2 3

Output:
1

Explanation:
The set can be {2}

*/

#include <algorithm>
#include <iostream>
#include <vector>

#define N 100010

std::vector<int> adj[N];
int dp[2][N]; // dp[parent taken = true/false][node]

int dfs(int curr, int parent, int par_taken)
{
    if (adj[curr].size() == 0) // Base case (leaf node)
        return par_taken == 1 ? 0 : 1;
    else if (dp[par_taken][curr] != -1) // Already memoized ans
        return dp[par_taken][curr];
    else
    {
        // Calculate result if we take this node
        int take = 1;
        for (auto& child : adj[curr])
            if (child != parent)
                take += dfs(child, curr, 1);
        
        dp[par_taken][curr] = take;
        
        if (par_taken == 1) // Parent was taken, we can also skip this node
        {
            int skip = 0;
            for (auto& child : adj[curr])
                if (child != parent)
                    skip += dfs(child, curr, 0);
            
            // Result is the minimum
            dp[par_taken][curr] = std::min(take, skip);
        }
        
        return dp[par_taken][curr];
    }
}

int main()
{
    int n;
    std::cin >> n;
    
    std::fill(dp[0], dp[0] + n + 1, -1);
    std::fill(dp[1], dp[1] + n + 1, -1);
    
    for (int i = 1; i < n; ++i)
    {
        int s, d;
        std::cin >> s >> d;
        
        adj[s].push_back(d);
        adj[d].push_back(s);
    }
    
    // Take or don't take root ? -> Act as if its parent was taken
    std::cout << dfs(1, -1, 1) << std::endl;
    
    return 0;
}
