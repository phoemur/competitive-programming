/*PERMUT1 - Permutations
#dynamic-programming

Let A = [a1,a2,...,an] be a permutation of integers 1,2,...,n. A pair of indices (i,j), 1<=i<=j<=n, is an inversion of the permutation A if ai>aj. We are given integers n>0 and k>=0. What is the number of n-element permutations containing exactly k inversions?

For instance, the number of 4-element permutations with exactly 1 inversion equals 3.
Task

Write a program which for each data set from a sequence of several data sets:

    reads integers n and k from input,
    computes the number of n-element permutations with exactly k inversions,
    writes the result to output. 

Input

The first line of the input file contains one integer d, 1<=d<=10, which is the number of data sets. The data sets follow. Each data set occupies one line of the input file and contains two integers n (1<=n<=12) and k (0<=k<=98) separated by a single space.
Output

The i-th line of the output file should contain one integer - the number of n-element permutations with exactly k inversions.
Example

Sample input:
1 
4 1 

Sample output:
3 

*/

#include <cstring>
#include <iostream>

// Ilustrates recurrence relation (but will not TLE)
int solve_recursive(int n, int k)
{
    if (n == 0)
        return 0;
    else if (k == 0)
        return 1;
    else
    {
        int res = 0;
        for (int i = 0; i < n && k - i >= 0; ++i)
            res += solve_recursive(n - 1, k - i);
        
        return res;
    }
}

int main()
{
    int dp[13][100]; // constraints defined in the problem description
    std::memset(dp, 0, sizeof(int) * 13 * 100);
    
    for (int i = 1; i < 13; ++i)
        dp[i][0] = 1;
    for (int i = 1; i < 13; ++i)
        for (int j = 1; j < 100; ++j)
            for (int x = 0; x < i && j - x >= 0; ++x)
                dp[i][j] += dp[i-1][j-x];
    
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        int n, k;
        std::cin >> n >> k;

        std::cout << dp[n][k] << std::endl;
    }
    
    return 0;
}
