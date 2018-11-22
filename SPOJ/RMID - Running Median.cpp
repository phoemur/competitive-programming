/*RMID - Running Median
#tree #binary-search

You will be given some integers in non decreasing order and each time the median is queried you have to report and remove it. Take the smaller element as median in case of even elements.
Input

The input contains many test cases. Read until End Of File.

Each test case contains n (n ≤ 100000) positive integers in non-decreasing order, along with m queries indicated by -1, all on separate lines. (See the example.)

For a query, print the current median on a single line and remove it from the list. 

Each test case ends with 0 on a single line, and two test cases will be separated by an empty line. All integers are guaranteed to fit in a signed 32-bit container. A query can only occur if the list is non-empty. 
Output

For each test case output m lines containing the answers to the corresponding queries. Print an empty line after each test case. 
Example

Input:
1
2
3
4
-1
-1
5
6
7
-1
0

2
3
-1
0

Output:
2
3
5

2

*/

#include <algorithm>
#include <cstdio>
#include <queue>
                         
int main()
{
    // Max heap to store smaller half elements
    std::priority_queue<long> s;
        
    // Min heap to store greater half elements
    std::priority_queue<long, std::vector<long>, std::greater<long>> g;
        
    long n;
        
    while (std::scanf("%ld", &n) != EOF)
    {
        if (n == 0) // End of this test case
        {
            std::printf("\n");
            s = {};
            g = {};
            continue;
        }
        
        long sz_s = s.size();
        long sz_g = g.size();
        long median;
            
        // Find median
        if (sz_s == sz_g)
        {
            if (sz_s == 0) // Empty
            {
                s.push(n);
                continue;
            }
            else
            {
                median = std::min(s.top(), g.top());
            }
        }
        else if (sz_s > sz_g)
            median = s.top();
        else
            median = g.top();
            
        // Queries
        if (n == -1) // Print and remove
        {
            std::printf("%ld\n", median);
                
            if (sz_s == 0)
                g.pop();
            else if (sz_g == 0 || median == s.top())
                s.pop();
            else
                g.pop();
        }
        else
        {
            if (n >= median)
            {
                if (sz_s >= sz_g)
                    g.push(n);
                else
                {
                    s.push(g.top());
                    g.pop();
                    g.push(n);
                }
            }
            else
            {
                if (sz_s <= sz_g)
                    s.push(n);
                else
                {
                    g.push(s.top());
                    s.pop();
                    s.push(n);
                }
            }
        }
    }
    
    return 0;
}
