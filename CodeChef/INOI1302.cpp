/*Indian National Olympiad in Informatics 2013

N people live in Sequence Land. Instead of a name, each person is identified by a sequence of integers, called his or her id. Each id is a sequence with no duplicate elements. Two people are said to be each other’s relatives if their ids have at least K elements in common. The extended family of a resident of Sequence Land includes herself or himself, all relatives, relatives of relatives, relatives of relatives of relatives, and so on without any limit.

Given the ids of all residents of Sequence Land, including its President, and the number K, find the number of people in the extended family of the President of Sequence Land.

For example, suppose N = 4 and K = 2. Suppose the President has id (4, 6, 7, 8) and the other three residents have ids (8, 3, 0, 4), (0, 10), and (1, 2, 3, 0, 5, 8). Here, the President is directly related to (8, 3, 0, 4), who in turn is directly related to (1, 2, 3, 0, 5, 8). Thus, the President’s extended family consists of everyone other than (0, 10) and so has size 3.
Input format

• Line 1: Two space-separated integers, N followed by K.

• Lines 2 to N + 1: Each line describes an id of one of the residents of Sequence Land, beginning with the President on line 2. Each line consists of an integer p, followed by p distinct integers, the id.
Output format

The output consists of a single integer, the number of people in the extended family of the President.
Test Data

The testdata is grouped into two subtasks. In both subtasks, 1 ≤ N ≤ 300 and 1 ≤ K ≤ 300. Each number in each id is between 0 and 109 inclusive.

• Subtask 1 [30 points]: The number of elements in each id is between 1 and 10 inclusive.

• Subtask 2 [70 points]: The number of elements in each id is between 1 and 300 inclusive.
Example

Here is the sample input and output corresponding to the example above.
Sample input 

4 2
4 4 6 7 8
4 8 3 0 4
2 0 10
6 1 2 3 0 5 8

Sample output

3
*/

#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>

bool connected(const std::vector<long>& lhs, 
               const std::vector<long>& rhs,
               unsigned k)
{
    std::vector<long> tmp;
    tmp.reserve(std::max(lhs.size(), rhs.size()));
    
    std::set_intersection(lhs.begin(), lhs.end(), 
                          rhs.begin(), rhs.end(), 
                          std::back_inserter(tmp));
    
    return tmp.size() >= k;
}

int main()
{
    int n, k;
    std::scanf("%d %d", &n, &k);
    
    std::vector<std::vector<int>> graph (n); // Adjacency List
    std::vector<std::vector<long>> input; // Input array
    
    // Input
    for (int i = 0; i < n; ++i)
    {
        int num;
        std::scanf("%d", &num);
        
        std::vector<long> tmp (num);
        
        for (int j = 0; j < num; ++j)
            std::scanf("%ld", &tmp[j]);
        
        std::sort(tmp.begin(), tmp.end());
        
        input.push_back(std::move(tmp));
    }
    
    // Fill Adjacency list
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (connected(input[i], input[j], k))
            {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }
    
    // Compute result
    std::vector<bool> visited (n, false);
    std::vector<int> result;
    result.reserve(n);
    
    // BFS
    std::queue<int> Q;
    Q.push(0);
    visited[0] = true;
    
    while (!Q.empty())
    {
        int cur = Q.front();
        Q.pop();
        
        result.push_back(cur);
        
        for (int c : graph[cur])
            if (!visited[c])
            {
                Q.push(c);
                visited[c] = true;
            }
    }
    
    
    std::printf("%lu\n", result.size());
    
    return 0;
}
