/*ETF - Euler Totient Function
#number-theory #totient

In number theory, the totient φ of a positive integer n is defined to be the number of positive integers less than or equal to n that are coprime to n.

Given an integer n (1 <= n <= 10^6). Compute the value of the totient φ.
Input

First line contains an integer T, the number of test cases. (T <= 20000)

T following lines, each contains an integer n.
Output

T lines, one for the result of each test case.
Example

Input:
5
1
2
3
4
5

Output:
1
1
2
2
4

*/


#include <cstdint>
#include <iostream>

std::int64_t euler_totient(std::int64_t num)
{
    std::int64_t res = num;
    
    for (std::int64_t i = 2; i*i <= num; ++i)
    {
        if(num % i == 0)
            res -= res / i;

        while(num % i == 0)
            num /= i;
    }
    
    if(num > 1)
        res -= res / num;
    
    return res;
}

int main()
{
    int queries;
    std::cin >> queries;
    
    while (queries--)
    {
        std::int64_t num;
        
        if (std::cin >> num)
            std::cout << euler_totient(num) << std::endl;
    }
    
    return 0;
}
