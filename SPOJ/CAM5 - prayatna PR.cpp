/*CAM5 - prayatna PR
#dfs

help the Prayatna pr team

Well, the annual technical symposium of Department of Computer Technology is around the corner. All that we need, to make it a grand success is Publicity among the peer groups ( ofCourse the sponsors too :P ). We decided to share the job between the student groups. As per the plan we decided to meet people in person and influence them to attend Prayatna. But to meet them we have to go to various student groups. To do so, we had to cut our classes. But being studious. students refused to cut more classes. Instead of meeting every one in person we decided to meet few people such that the person to whom we pass the news will spread it to all his friends. And those friends will pass it to other friends and so on. Your task is to find the number of people to be met by the organizers to spread the news.

Caution: Large I/O
Input

First line of input is 't' - Test cases. Follwed by N, the number of peers in the testcase ( 0 to N-1 ). followed by the number of friend description 'e'. Following are 'e' descriptions of type "a b" denoting 'a' friends with 'b'. If 'a' is friends with 'b' then 'b' is friends with 'a'.
Output

Output contains t line, the number of people, the organizers have to meet in person for each test case.
Example

Input:
2

4
2
0 1
1 2

3
0

Output:
2
3

Explanation

case 1 : 0 is friends with 1; 1 is friends with 2; so if we pass the news to 0 & 3, news will pass it to the entire N peers.

case 2 : no one is friends with any one. So we have to meet every one in person.
Constraints

t = 10
2 <= N <= 100000
0 <= e <= N/2
*/

#include <cstdio>
#include <vector>

void DFSutil(int vertex, 
             std::vector<bool>& visited, 
             const std::vector<std::vector<int>>& adj)
{
    visited[vertex] = true;
    
    for (int v : adj[vertex])
        if (!visited[v])
            DFSutil(v, visited, adj);
}

/* Count the number of connected components in the graph */
int numConnected(const std::vector<std::vector<int>>& adj)
{
    int res = 0;
    std::vector<bool> visited (adj.size(), false);
    
    for (int i = 0; i < adj.size(); ++i)
        if (!visited[i])
        {
            DFSutil(i, visited, adj);
            ++res;
        }
        
    return res;
}

int main()
{
    int tests;
    std::scanf("%d", &tests);
    
    while (tests--)
    {
        int n, e;
        std::scanf("%d %d", &n, &e);
        
        std::vector<std::vector<int>> adj (n); // graph's adjacency list
        
        while (e--)
        {
            int a, b;
            std::scanf("%d %d", &a, &b);
            
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        
        std::printf("%d\n", numConnected(adj));
    }
    
    return 0;
}
