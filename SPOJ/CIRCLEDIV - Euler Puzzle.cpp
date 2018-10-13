/*CIRCLEDIV - Euler Puzzle
#geometry #combinatorics

 

Given some set of points on a circle, you connect every pair of them with a line, find the maximum number of sections do these lines cut the circle into?

Input

First line for each testcase file contains T denoting the no. of test queries followed by T numbers N, denoting the no. of point on a circle.
Constraints:

1<= T <= 100000 (105)

1<= N <= 100000 (105)

Note: Use fast I/O methods.
Output

For each test query, ouput the result in given format. As the result can be large answer the result modulus 1000000007 (109 +7).

Case <test_query_i>: <max_section_circle_cuts_into>
Example

Input:
3
1
2
6
Output:
Case 1: 1
Case 2: 2
Case 3: 31 
*/

#include <algorithm>
#include <cstdio>

#define MOD 1000000007

// http://oeis.org/A000127
int nCrmodP(int n, int k) {
    if (k == 0)
        return 1;
    else if (k > n)
        return 0;
    
    
    int d[5];
    for (int i = 1; i <= k; i ++) 
    {
        d[i] = n - i + 1;
    }
    
    for (int i = 2; i <= k; i ++)
    {
        int divider = i;
        for (int j = 1; j <= k; j ++) 
        {
            int g = std::__gcd(d[j], divider);
            d[j] /= g;
            divider /= g;
        }
    }
    
    int result = 1;
    for (int i = 1; i <= k; i ++)
    {
        result = 1LL * result * d[i] % MOD;
    }
    
    return result;
}

int main()
{
    int tests;
    std::scanf("%d", &tests);
    
    for (int i = 1; i <= tests; ++i)
    {
        int n;
        std::scanf("%d", &n);
        
        if (n < 6)
            std::printf("Case %d: %d\n", i, 1 << (n-1));
        else
            std::printf("Case %d: %d\n", i, (nCrmodP(n, 4) + nCrmodP(n, 2) + 1) % MOD);
    }
    
    
    return 0;
}
