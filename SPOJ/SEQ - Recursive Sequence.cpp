/*SEQ - Recursive Sequence
#recursion

Sequence (ai) of natural numbers is defined as follows:

   ai = bi (for i <= k)
   ai = c1ai-1 + c2ai-2 + ... + ckai-k (for i > k)

where bj and cj are given natural numbers for 1<=j<=k. Your task is to compute an for given n and output it modulo 1e9.
Input

On the first row there is the number C of test cases (equal to about 1000).
Each test contains four lines:

k - number of elements of (c) and (b) (1 <= k <= 10)
b1,...,bk - k natural numbers where 0 <= bj <= 109 separated by spaces
c1,...,ck - k natural numbers where 0 <= cj <= 109 separated by spaces
n - natural number (1 <= n <= 109)
Output

Exactly C lines, one for each test case: an modulo 109
Example

Input:
3 
3 
5 8 2 
32 54 6 
2 
3 
1 2 3 
4 5 6 
6 
3 
24 354 6 
56 57 465 
98765432

Output:
8 
714 
257599514

*/

#include <bits/stdc++.h>

#define MOD 1000000000

// Multiply 2 NxN (square) matrix % MOD
std::vector<std::vector<long>> operator*(const std::vector<std::vector<long>>& lhs, 
                                         const std::vector<std::vector<long>>& rhs)
{    
    int N = lhs.size();
    std::vector<std::vector<long>> res (N, std::vector<long>(N, 0));
    
    // Multiply -> O(n^3)
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int k = 0; k < N; ++k)
                res[i][j] = (res[i][j] + (lhs[i][k] * rhs[k][j])) % MOD;
        
    return res;
}

// Binary exponentiation of a square matrix
std::vector<std::vector<long>> power(std::vector<std::vector<long>> base, // pass by value to work on a copy
                                     int exp) 
{    
    int N = base.size();
    std::vector<std::vector<long>> res (N, std::vector<long>(N, 0));
    
    // Make res the identity matrix
    for (int i = 0; i < N; ++i)
        res[i][i] = 1;
    
    // Multiply by powers of 2 whose bit is set on exp
    while (exp > 0)
    {
        if (exp & 1)
            res = res * base;
        
        base = base * base; // Square the base
        exp >>= 1;
    }
    
    return res;
}

int main()
{
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        int k;
        std::cin >> k;
        
        // Input base vector
        std::vector<long> f1 (k);
        for (auto& elem: f1) std::cin >> elem;
        
        // Input and make transformation matrix
        std::vector<std::vector<long>> trf (k, std::vector<long>(k, 0));
        for (int i = 0; i + 1 < k; ++i)
            trf[i][i+1] = 1;
        for (int i = k-1; i >= 0; --i)
            std::cin >> trf[k-1][i];
        
        int n;
        std::cin >> n;
        
        if (n <= k) // Result already available, print
            std::cout << f1[n-1] << std::endl;
        else // Compute by matrix exponentiation
        {
            auto res = power(trf, n-k);
            
            long sum = 0;
            for (int i = k-1; i >= 0; --i)
                sum = (sum + res[k-1][i] * f1[i]) % MOD;
            
            std::cout << sum << std::endl;
        }
    }
    
    return 0;
}
