/*RMID2 - Running Median Again
#tree #heap #binary-search #priority-queue

Danish has just solved the problem Running Median.

The first line of the problem says "You will be given some integers in non-decreasing order". The problem asks you to report and remove the median of the list every time it is queried.

Having solved this problem, Danish now begins to wonder how to solve the problem if the input is in any order (not necessarily non-decreasing order as mentioned above).

Can you help him?

Your task is to take as input a list of positive integers. Whenever -1 is given as input, you must output the median of the list, and remove it from the list. Take the smaller element as the median in case of even number of elements.
Input

The input contains several test caes.

The first line contains an integer t, the number of test cases.

Each test case has several lines, each containing an integer n (<=10^9) . If n is positive, add it to the list. n=-1 indicates a median query (there will be no median query if the list is empty). The test case is terminated by n=0.

In each test case, there will be upto 10^5 integers to be added to the list, and upto 10^5 median queries.
Output

For each median query as described above, print the median on a new line.
Example

Input:
1
9
10
2
5
1
18
-1
-1
4
3
-1
8
7
-1
0

Output:
5
9
3
7

*/

#include <algorithm>
#include <cstdio>
#include <queue>
                         
int main()
{
    long tests;
    std::scanf("%ld", &tests);
    
    while (tests--)
    {
        // Max heap to store smaller half elements
        std::priority_queue<long> s;
        
        // Min heap to store greater half elements
        std::priority_queue<long, std::vector<long>, std::greater<long>> g;
        
        long n;
        
        while (std::scanf("%ld", &n) != EOF && n != 0)
        {
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
        
        std::printf("\n");
    }
    
    return 0;
}
