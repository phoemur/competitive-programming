/*MPOW - Power of matrix
#matrix

You will be given a square matrix M and a positive integer power N. You will have to compute M raised to the power N. (that is, M multiplied with itself N times.)
Input

First line of input is T ( number of test-cases) First line of each test-case contains two integer M , N where M is size of square matrix that we have to exponent and N is the power to which we have to exponent 
Next M lines describe the input matrix. Each line contains exactly M elements corresponding to each array
Output

Output M line corresponding to each row of resultant matrix Each line must have M integers where jth element of ith line is jth element of resultant matrix taken modulo with 1000000007 (10^9+7).

Simply , you have to print the resultant square matrix.
Example

Input:

2
2 3
1 0 
1 1 
3 3
1 0 4 
1 2 2 
0 4 4 


Output:

1 0 
3 1 
17 112 116 
15 88 100 
28 144 160 


constraints:

1<=T<=10

 1<=M<=50

1<=N<=100000

0<=each element of input matrix<=10^9*/

#include <bits/stdc++.h>

// Multiply a NxN (square) matrix % MOD
template<typename T>
auto operator*(const std::vector<std::vector<T>>& lhs, 
               const std::vector<std::vector<T>>& rhs)
{
    static_assert(std::is_arithmetic<T>::value, 
                  "Matrix multiplication on non-arithmetic type");
    assert(lhs.size() == rhs.size());
    assert(lhs[0].size() == rhs[0].size());
    
    int N = lhs.size();
    
    std::vector<std::vector<T>> res (N, std::vector<T>(N, T{}));
    
    // Multiply -> O(n^3)
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int k = 0; k < N; ++k)
                res[i][j] = (res[i][j] + (lhs[i][k] * rhs[k][j])) % 1000000007;
        
    return res;
}

// Binary exponentiation of a square matrix
template<typename T>
auto power(std::vector<std::vector<T>> base, int exp) // pass by value to work on a copy
{    
    int N = base.size();
    std::vector<std::vector<T>> res (N, std::vector<T>(N, T{}));
    
    // Make res the identity matrix
    for (int i = 0; i < N; ++i)
        res[i][i] = 1;
    
    // Multiply by powers of 2 whoose bit is set on exp
    while (exp > 0)
    {
        if (exp & 1)
            res = res * base;
        
        base = base * base;
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
        int sz, exp;
        std::cin >> sz >> exp;
        
        std::vector<std::vector<long>> mat (sz, std::vector<long>(sz));
        
        for (auto& row: mat)
            for (auto& elem: row)
                std::cin >> elem;
            
        auto res = power(mat, exp);
        
        for (int i = 0; i < sz; ++i)
        {
            for (int j = 0; j < sz; ++j)
            {
                std::cout << res[i][j];
                
                if (j == sz - 1)
                    std::cout << std::endl;
                else
                    std::cout << " ";
            }
        }
    }
    
    return 0;
}
