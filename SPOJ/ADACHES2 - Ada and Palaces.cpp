/*ADACHES2 - Ada and Palaces
#dynamic-programming #chess #sequences

Ada the Ladybug was playing chess agains her good friend Velvet Mite Vinit. They came up with new figure, called palace. In fact, palace is just tower with king inside. It can attack as king and tower combined: Either anywhere to same column or row or anywhere to adjacent (by side or diagonal) field.

Their question is simple: How many ways can N palaces be placed on NxN chessboard so none of them attacks any other. Since this number might be pretty big, output answer modulo 109+7
Input

The first line of input will contain 1 ≤ T ≤ 105, the number of test-cases.

Each of the testcases will contain single integer 1 ≤ N ≤ 107, the size of chessboard.
Output

For each test-case output the number of possibilities modulo 1000000007.
Example Input

8
1
2
3
7
10
1000
10000
9999999

Example Output

1
0
0
646
479306
711794305
450342414
838796194

*/

#include <iostream>
#include <vector>

#define MOD 1000000007

// http://oeis.org/A002464 -> OEIS rocks
// Google Hertzsprung's problem: The number of ways to arrange n non-attacking kings on an n X n board, with 1 in each row and column.

// Ilustrates recurrence relation
long solve_recursive(int n)
{
    if (n == 0 || n == 1)
        return 1;
    else if (n == 2 || n == 3)
        return 0;
    else
    {
        return (n+1)*solve_recursive(n-1) - 
               (n-2)*solve_recursive(n-2) - 
               (n-5)*solve_recursive(n-3) + 
               (n-3)*solve_recursive(n-4);
    }
}

int main()
{
    std::vector<long> dp (10000001);
    
    dp[0] = dp[1] = 1;
    dp[2] = dp[3] = 0;
    
    for (int i = 4; i < 10000001; ++i)
    {
        dp[i] = (i+1)*dp[i-1] % MOD;
        dp[i] = (dp[i] - ((i-2)*dp[i-2] % MOD) + MOD) % MOD;
        dp[i] = (dp[i] - ((i-5)*dp[i-3] % MOD) + MOD) % MOD;
        dp[i] =  dp[i] +  (i-3)*dp[i-4] % MOD;
    }
    
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        int n;
        std::cin >> n;
        //std::cout << solve_recursive(n) << std::endl;
        std::cout << dp[n] % MOD << std::endl;
    }
    
    return 0;
}
