/*FIBOSUM - Fibonacci Sum
no tags 

The fibonacci sequence is defined by the following relation:

    F(0) = 0
    F(1) = 1
    F(N) = F(N - 1) + F(N - 2), N >= 2

Your task is very simple. Given two non-negative integers N and M, you have to calculate the sum (F(N) + F(N + 1) + ... + F(M)) mod 1000000007.
Input

The first line contains an integer T (the number of test cases). Then, T lines follow. Each test case consists of a single line with two non-negative integers N and M.
Output

For each test case you have to output a single line containing the answer for the task.
Example

Input:
3
0 3
3 5
10 19

Output:
4
10
10857

Constraints

    T <= 1000
    0 <= N <= M <= 109

*/

#include <array>
#include <cstdint>
#include <iostream>
#include <utility>


using matrix = std::array<std::array<std::uint64_t, 2>, 2>;

constexpr static int MOD = 1000000007;

void mul(matrix& a, const matrix& b)
{
    matrix res = {{{0,0}, {0,0}}};
    
    for(int i = 0 ; i < 2 ; i ++)
        for(int j = 0 ; j < 2 ; j++)
            for(int k = 0 ; k < 2 ; k++)
                res[i][j] = (res[i][j] + a[i][k]*b[k][j]) % MOD;
    
    a = std::move(res);
}

std::uint64_t fib(std::uint64_t  n)
{
    matrix mat  = {{{1 , 1} , {1 , 0}}};
    matrix temp = {{{1 , 0} , {0 , 1}}};

    while(n)
    {
        if(n & 1)
            mul(temp, mat);

        mul(mat, mat);
        n /= 2;
    }
    
    return temp[0][1];
}

int main()
{
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        int n, m;
        std::cin >> n >> m;
        
        std::cout << (fib(m+2) - fib(n+1) + MOD) % MOD << std::endl;
    }
    
    return 0;
}
