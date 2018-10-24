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

#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <vector>

long solve(const int i, 
           const int j, 
           const std::vector<int>& arr, 
           std::vector<std::vector<int>>& dp)
{
    if (i >= j)
        return 0;
    else if (dp[i][j] != -1)
        return dp[i][j];
    else
    {
        long res = std::numeric_limits<int>::max();
        
        for (int k = i; k < j; ++k)
        {
            static auto sum_mod = [](int a, int b){return (a + b) % 100;};
            
            int csum1 = std::accumulate(std::begin(arr)+i, 
                                        std::begin(arr)+k+1, 
                                        0, 
                                        sum_mod);
            
            int csum2 = std::accumulate(std::begin(arr)+k+1, 
                                        std::begin(arr)+j+1, 
                                        0, 
                                        sum_mod);

            res = std::min(res, solve(i, k, arr, dp) + solve(k+1, j, arr, dp) + (csum1*csum2));
        }
        
        dp[i][j] = res;
        return res;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int n;
    while (std::cin >> n)
    {
        std::vector<int> arr (n);
        std::vector<std::vector<int>> dp (n, std::vector<int>(n, -1));
        
        std::copy_n(std::istream_iterator<int>(std::cin), n, std::begin(arr));
        
        std::cout << solve(0, n-1, arr, dp) << std::endl;
    }
    
    return 0;
}
