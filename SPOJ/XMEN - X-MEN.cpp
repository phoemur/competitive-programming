/*XMEN - X-MEN
#dynamic-programming

Dr. Charles Xavier is trying to check the correlation between the DNA samples of Magneto and Wolverine. Both the DNAs are of length N, and can be described by using all integers between 1 to N exactly once. The correlation between two DNAs is defined as the Longest Common Subsequence of both the DNAs.
Help Dr. Xavier find the correlation between the two DNAs.
Input :

First line of input contains number of Test Cases T.
ach test case starts with an integer N, size of DNA.
Next two lines contains N integers each, first line depicting the sequence of Magneto's DNA and second line depicting Wolverine's DNA.
Output :

For each test case print one integer, the correlation between the two DNAs.
Sample Input :

2
2
1 2
2 1
3
1 2 3
1 3 2

Sample Output :

1
2

Constraints :

1 ≤ T ≤ 10
1 ≤ N ≤ 100000
*/

#include <algorithm>
#include <cstdio>
#include <vector>

static const int INF = 1 << 29;

int LIS(const std::vector<int>& vec)
{
    const int n = vec.size();

    std::vector<int> d (n+1, INF);
    d[0] = -INF;
    int ans = 0;
    
    for (int i = 0; i < n; i++)
    {
        auto it = std::upper_bound(d.begin(), d.end(), vec[i]);
        int j = std::distance(d.begin(), it);
        
        if (d[j-1] < vec[i] && vec[i] < d[j])
        {    
            d[j] = vec[i];
            ans = std::max(ans, j);
        }
    }

    return ans;
}

int main()
{
    int tests, temp;
    std::scanf("%d", &tests);
    
    std::vector<int> a, b;
        
    while (tests--)
    {
        int n;
        std::scanf("%d", &n);
        
        a.resize(n+1);
        b.resize(n+1);
        
        // First vector will store indexes
        for (int i = 0; i < n; ++i)
        {
            std::scanf("%d", &temp);
            
            a[temp] = i;
        }
        
        // Second vector elements indexed by first one
        for (int i = 0; i < n; ++i)
        {
            std::scanf("%d", &temp);
            
            b[i] = a[temp];
        }
        
        // LIS O(nlogn)
        std::printf("%d\n", LIS(b));
    }
    
    return 0;
}
