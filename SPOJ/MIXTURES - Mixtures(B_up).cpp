/*MIXTURES - Mixtures
#dynamic-programming

Harry Potter has n mixtures in front of him, arranged in a row. Each mixture has one of 100 different colors (colors have numbers from 0 to 99).

He wants to mix all these mixtures together. At each step, he is going to take two mixtures that stand next to each other and mix them together, and put the resulting mixture in their place.

When mixing two mixtures of colors a and b, the resulting mixture will have the color (a+b) mod 100.

Also, there will be some smoke in the process. The amount of smoke generated when mixing two mixtures of colors a and b is a*b.

Find out what is the minimum amount of smoke that Harry can get when mixing all the mixtures together.
Input

There will be a number of test cases in the input.

The first line of each test case will contain n, the number of mixtures, 1 <= n <= 100.

The second line will contain n integers between 0 and 99 - the initial colors of the mixtures.
Output

For each test case, output the minimum amount of smoke.
Example

Input:
2
18 19
3
40 60 20

Output:
342
2400

In the second test case, there are two possibilities:

    first mix 40 and 60 (smoke: 2400), getting 0, then mix 0 and 20 (smoke: 0); total amount of smoke is 2400
    first mix 60 and 20 (smoke: 1200), getting 80, then mix 40 and 80 (smoke: 3200); total amount of smoke is 4400 

The first scenario is a much better way to proceed. */

#include <iostream>
#include <vector>

static const int INF = 1 << 30;

template<typename T>
T minimum(T t1, T t2)
{
    return t1 < t2 ? t1 : t2;
}

int solve_bottom_up(const std::vector<int>& preffix_sum)
{
    const int n = preffix_sum.size() - 1;

    // DP vector
    std::vector< std::vector<int> > dp (n, std::vector<int>(n));
    
    // Base cases
    for (int i =0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (i >= j)
                dp[i][j] = 0;
            else
                dp[i][j] = INF;
    
    // Fill table
    for (int j = 1; j < n; ++j)
    {
        for (int i = j-1; i >= 0; --i)
        {
            for (int k = i; k < j; ++k)
            {
                int csum1 = (preffix_sum[k+1] - preffix_sum[i])   % 100;            
                int csum2 = (preffix_sum[j+1] - preffix_sum[k+1]) % 100;
                    
                dp[i][j] = minimum(dp[i][j], 
                                   dp[i][k] + dp[k+1][j] + (csum1*csum2));
            }
        }
    }
    
    return dp[0][n-1];
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int n;
    while (std::cin >> n)
    {
        // Input as Preffix Sum vector
        std::vector<int> preffix_sum (n+1);        
        preffix_sum[0] = 0;
        
        for (int i = 1; i <= n; ++i)
        {
            std::cin >> preffix_sum[i];
            preffix_sum[i] += preffix_sum[i-1];
        }
        
        // Solve
        std::cout << solve_bottom_up(preffix_sum) << std::endl;
    }
    
    return 0;
}
