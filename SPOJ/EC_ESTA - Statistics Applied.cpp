/* EC_ESTA - Statistics Applied
no tags 

In this problem we will be looking for medians of data set. Median is the central element in ordered data group. For example: for the set {2,6,3,3,2} the median would be 3. In general, if we have n elements {a1, a2, a3 ... an}, we define the median as element a(n+1)/2 if n is odd and (an/2+an/2+1)/2 otherwise.

You will be given N numbers and you must calculate N medians. i-th median is taken on the subset [a1, a2, a3, .., ai] for 1 <= i <= N.
Input

The first line contains the number of test cases. Each case consists of an integer N (1 <= N <= 100000). N integers ai (0 <= ai <231) follow, elements in data set.
Output

For each case, print N lines with the medians. If the result is non-integral, print the exact value using decimal point (see example).
Example

Input:
2
4
3 5 7 3
2
3 4

Output:
3
4
5
4
3
3.5

*/

#include <cstdio>
#include <functional>
#include <queue>


int main()
{    
    int tests;
    std::scanf("%d", &tests);
    
    while (tests--)
    {
        std::priority_queue<long> g;
        std::priority_queue<long, std::vector<long>, std::greater<long>> s;
        
        int n;
        std::scanf("%d", &n);
        
        long median = -1;
        
        while (n--)
        {   
            long num;
            std::scanf("%ld", &num);
            
            if(num <= median || median == -1) g.push(num);
            else s.push(num);
                        
            if (s.size() > g.size())
            {
                g.push(s.top());
                s.pop();
            }
            
            if (g.size() - s.size() > 1)
            {
                s.push(g.top());
                g.pop();
            }
            
            if (s.size() == g.size())
            {
                double ans = static_cast<double>(s.top() + g.top()) / 2.0;
                median = static_cast<long>(ans); // floor the result
            
                if (ans - median == 0)
                    std::printf("%ld\n", median);
                else
                    std::printf("%ld.5\n", median);
            }    
            else
            {
                median = g.top();
                std::printf("%ld\n", median);
            }
        }
    }
    
    return 0;
}
