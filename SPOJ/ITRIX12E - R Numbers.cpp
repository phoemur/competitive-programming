/*ITRIX12E - R Numbers
#matrix #linear-recurrence #digit-dp-1

R - Numbers

R-numbers are numbers which have the property that they do not have the digit '0 ' and sum of every two adjacent digits of the number is prime. 123 is a R-number because 1+2 =3 and 2+3 =5 and 3 , 5 are primes.

How many R-numbers can be formed with atmost length N?

i.e R-numbers of length 1 + R-numbers of length 2 + R-numbers of length 3+....... R-numbers of length N

Length of a number = Number of digits in the number

Only four single digit numbers are R-numbers which are nothing but single digit primes 2,3,5,7
Input Specification

The first line of the input file contains T which denotes the number of Test cases.The next T lines contain an integer N <= 10^9
Output Specification

Print the numbers of R-numbers modulo 1000000007. [10^9+7];
Example

Sample Input:
2
1
2

Sample Output:
4
33

*/

#include <bits/stdc++.h>

#define MOD 1000000007

// Based on solution from Arnaud Desombre on https://ideone.com/6ATT6k

// Multiply a NxN (square) matrix
template<typename T, std::size_t N>
auto operator*(const std::array<std::array<T,N>,N>& lhs, 
               const std::array<std::array<T,N>,N>& rhs)
{
    static_assert(std::is_arithmetic<T>::value, 
                  "Matrix multiplication on non-arithmetic type");
    
    std::array<std::array<T,N>,N> res {};
    
    // Multiply -> O(n^3)
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int k = 0; k < N; ++k)
                res[i][j] = (res[i][j] + lhs[i][k] * rhs[k][j]) % MOD;
        
    return res;
}

// Binary exponentiation of a square matrix
template<typename T, std::size_t N>
auto power(std::array<std::array<T,N>,N> base, int exp) // pass by value
{
    static_assert(std::is_arithmetic<T>::value, 
                  "Matrix multiplication on non-arithmetic type");
    
    std::array<std::array<T,N>,N> res {};
    
    // Make res the identity matrix
    for (int i = 0; i < N; ++i)
        res[i][i] = 1;
    
    // Multiply by powers of 2 whose bit is set on exp
    while (exp > 0)
    {
        if (exp & 1)
            res = res * base;

        base = base * base;

        exp >>= 1;
    }

    return res;
}

long solve(int n)
{
    std::array<std::array<long,10>,10> transform 
        {{{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
          {0, 1, 1, 0, 1, 0, 1, 0, 0, 0},
          {0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
          {0, 0, 1, 0, 1, 0, 0, 0, 1, 0},
          {0, 1, 0, 1, 0, 0, 0, 1, 0, 1},
          {0, 0, 1, 0, 0, 0, 1, 0, 1, 0},
          {0, 1, 0, 0, 0, 1, 0, 1, 0, 0},
          {0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
          {0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
          {0, 0, 1, 0, 1, 0, 0, 0, 1, 0}}};
          
    std::array<long,10> f2 {{4, 4, 4, 3, 4, 3, 3, 2, 3, 3}};
    
    if (n <= 0)
        return 0;
    else if (n == 1)
        return 4;
    else
    {   
        auto res = power(transform, n-2);
        
        long total = 0;
        
        for (int i = 0; i < 10; ++i)
            for (int j = 0; j < 10; ++j)
                total = (total + res[i][j] * f2[j]) % MOD;
            
        return total;
    }
}

int main()
{
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        int n;
        std::cin >> n;
        std::cout << solve(n) << std::endl;
    }
        
    return 0;
}
