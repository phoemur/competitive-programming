/*You are given a directed acyclic graph with N vertices (numbered 1 through N) and M

edges. You want to destroy it all! To destroy the graph, you should delete all of its vertices.

In one step, you are allowed to delete at most two vertices; you may only delete a vertex when there is no edge from it to another (not yet deleted) vertex. You may not delete two vertices when there is an edge between them either.

Find a way to destroy the graph in the minimum number of steps.
Input

    The first line of the input contains two space-separated integers N

and M
.
Each of the next M
lines contains two space-separated integers U and V denoting an edge from vertex U to vertex V

    .

Output

    The first line of the output should contain a single integer S

denoting the minimum number of steps needed to destroy the graph.
Each of the next S
lines should describe one step; it should contain an integer K (1≤K≤2), followed by a space and K

    space-separated integers denoting the numbers of vertices deleted in this step.

Constraints

    1≤N,M≤106

    the graph on the input does not contain any cycles or self-loops

Scoring

The score for each test file is 10⋅(C/S)2
, where C is the number of steps in which you deleted exactly 2

vertices. The final score of your submission is equal to the sum of scores for each test file.

There are twenty test cases. During the contest, the displayed score will account for exactly four test files, i.e. your score reflects your submission's performance on 20% (4/20) of the test files. However, if your program gets a non-AC verdict on any test file, your submission's verdict will be non-AC. In other words, an AC verdict denotes that your program runs successfully on all the test files. After the end of the contest, your score will be changed to include the sum of your program's scores over the other sixteen test files.
Example Input

6 6
1 2
2 3
1 3
3 4
3 5
1 6

Example Output

4
2 4 5
2 6 3
1 2
1 1
*/

#include <bits/stdc++.h>

#define N 1000001

std::vector<int> adj[N];
int outdegree[N];
int  indegree[N];
std::vector<int> parents[N];

inline void init(int n)
{
    std::memset(indegree,  0, sizeof(int) * N);
    std::memset(outdegree, 0, sizeof(int) * N);
}

std::list<int> kahn_top_sort(int n)
{
    std::queue<int> q;
    
    for (int i = 1; i <= n; ++i)
        if (indegree[i] == 0)
            q.push(i);
        
    std::list<int> top_order;
    
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        top_order.push_back(u);
 
        for (auto& elem : adj[u])
        {
            --indegree[elem];
            
            if (indegree[elem] == 0)
                q.push(elem);
        }
    }
    
    return top_order;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    init(n);
    
    while (m--)
    {
        int u, v;
        std::cin >> u >> v;
        
        adj[u].push_back(v);
        outdegree[u]++;
        indegree[v]++;
        parents[v].push_back(u);
    }
    
    auto tmp = kahn_top_sort(n);
    
    /*
    for (auto& elem : tmp) std::printf("%d ", elem);
    std::printf("\n");
    for (auto& elem : tmp) std::printf("%d ", indegree[elem]);
    std::printf("\n");
    for (auto& elem : tmp) std::printf("%d ", outdegree[elem]);
    std::printf("\n");
    */
    
    std::vector<std::string> ans;
    ans.reserve(n+1);
    
    while (tmp.size() > 0)
    {        
        // find first with outdegree == 0
        int a1;
        
        for (auto it = tmp.rbegin(); it != tmp.rend(); ++it)
            if (outdegree[*it] == 0)
            {
                a1 = *it;
                tmp.erase(std::next(it).base());
                break;
            }
        
        // Try to find another one with outdegree 0
        int a2 = -1;
        for (auto it = tmp.rbegin(); it != tmp.rend(); ++it)
            if (outdegree[*it] == 0)
            {
                a2 = *it;
                tmp.erase(std::next(it).base());
                break;
            }
        
        
        if (a2 != -1)
        {            
            ans.push_back("2 " + std::to_string(a2) + " " + std::to_string(a1));
            
            for (auto& elem: parents[a2])
                outdegree[elem]--;
        }
        else
        {
            ans.push_back("1 " + std::to_string(a1));
        }
        
        for (auto& elem: parents[a1])
            outdegree[elem]--;
    }
    
    std::cout << ans.size() << "\n";
    
    for (auto& elem: ans)
        std::cout << elem << "\n";
    
    return 0;
}
