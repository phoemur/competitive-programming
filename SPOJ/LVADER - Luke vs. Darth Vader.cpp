/*LVADER - Luke vs. Darth Vader
#combinatorics

You know one of the most dangerous villain of all time, it's Darth Vader. It's time to stop him and Master Luke is looking forward to fight against him. They both are in an infinite two-dimensional grid. Each cell is denoted by (x, y). Here x denotes the row number and y denotes the column number of that cell. Please have a look on that picture of 5*7 grid to understand.

Luke stays at a cell (x1, y1) and Vader stays at another cell (x2, y2). It is guaranteed that x1<=x2 and y1<=y2. Master Luke need to reach to the Vader’s cell. Each time Luke can move one step below horizontally or vertically or diagonally. That means, if his position is (x, y) then he can move to (x+1, y) or (x, y+1) or (x+1, y+1) cell in a single move. Given Luke and Vader’s position you have to determine in how many ways Luke can reach to the Vader’s cell. As the answer can be very large output the solution modulo 10^9 + 7.
Input

Input starts with an integer (T<=50) which denotes the number of test case. Each test case consists four integer x1, y1, x2, y2 (0<=x1<=x2<=100000 and 0<=y1<=y2<=100000), the position of Luke and Vader.
Output

For each test case, print the number of ways Luke can reach to the Vader’s cell modulo 10^9 + 7.
Example

Input:

3

1 2 2 3

2 2 3 3
3 4 3 5

Output:

Case 1: 3

Case 2: 3
Case 3: 1

Explanation:

In the first case he can move from (1, 2) to (2, 3) in the following 3 ways,  
(1, 2) --> (1, 3) --> (2, 3)
(1, 2) --> (2, 2) --> (2, 3)
(1, 2) --> (2, 3)*/

#include <bits/stdc++.h>

#define MOD 1000000007

// Recurrence relation -> TLE
long solve_recursive(int x1, int y1, int x2, int y2)
{
     if (x1 > x2 || y1 > y2)
         return 0;
     else if (x1 == x2 || y1 == y2)
         return 1;
     else
         return solve_recursive(x1+1, y1,   x2, y2) + 
                solve_recursive(x1,   y1+1, x2, y2) + 
                solve_recursive(x1+1, y1+1, x2, y2);
}

// Dynamic programming -> TLE
long solve_DP(int x1, int y1, int x2, int y2)
{
    std::vector<std::vector<long>> dp (2, std::vector<long>(y2-y1+1));
    
    for (int i = 0; i <= x2-x1; ++i)
    {
        for (int j = 0; j <= y2-y1; ++j)
        {
            if (i == 0 || j == 0)
                dp[1][j] = 1;
            else
                dp[1][j] = (dp[0][j] + dp[1][j-1] + dp[0][j-1]) % MOD;
        }
        
        std::iter_swap(&dp[0], &dp[1]);
    }
    
    return dp[0][y2-y1];
}

// Now lets solve with Delannoy Numbers and nCr % p using using Fermat Little Theorem
// https://en.wikipedia.org/wiki/Delannoy_number

long fac[200002]; // Array storing factorial[idx] % MOD

long power(long x, long y, long p) 
{ 
    long res = 1;      // Initialize result 
  
    x = x % p;  // Update x if it is more than or 
                // equal to p 
  
    while (y > 0) 
    { 
        // If y is odd, multiply x with result 
        if (y & 1) 
            res = (res*x) % p; 
  
        // y must be even now 
        y = y>>1; // y = y/2 
        x = (x*x) % p; 
    }
    
    return res; 
} 
  
// Returns n^(-1) mod p 
long modInverse(long n, long p) 
{ 
    return power(n, p-2, p); 
} 
  
// Returns nCr % p using Fermat's little 
// theorem. 
long nCrModPFermat(long n, long r, long p) 
{ 
   // Base case 
   if (r==0) 
      return 1; 
    
    return (fac[n]* modInverse(fac[r], p) % p * 
            modInverse(fac[n-r], p) % p) % p; 
} 

int main()
{
    // Build Factorial array
    fac[0] = 1;
    for (int i = 1; i < 200002; ++i)
        fac[i] = fac[i-1] * i % MOD;
    
    int tests;
    std::cin >> tests;
    
    for (int cas = 1; cas <= tests; ++cas)
    {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        
        int m = x2 - x1;
        int n = y2 - y1;
        
        long res = 0;
        
        for (int k = 0; k <= std::min(m, n); ++k)
            res = (res + (nCrModPFermat(m + n - k, m, MOD) * nCrModPFermat(m, k, MOD))) % MOD;
        
        std::cout << "Case " << cas << ": " 
                  << res << std::endl;
    }
    
    return 0;
}
