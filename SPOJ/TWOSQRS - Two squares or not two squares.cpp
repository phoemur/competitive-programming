/*TWOSQRS - Two squares or not two squares
#number-theory

Given integer n decide if it is possible to represent it as a sum of two squares of integers.
Input

First line of input contains one integer c <= 100 - number of test cases. Then c lines follow, each of them consisting of exactly one integer 0 <= n <= 10^12.
Output

For each test case output Yes if it is possible to represent given number as a sum of two squares and No if it is not possible.
Example

Input:
10
1
2
7
14
49
9
17
76
2888
27

Output:
Yes
Yes
No
No
Yes
Yes
Yes
No
Yes
No

*/

#include <cstring>
#include <iostream>
#include <vector>

#define MAX 1000000
#define LIM 1000
#define ifComp(x) (flagArr[x>>6]&(1<<((x>>1)&31)))
#define isComp(x) (flagArr[x>>6]|=(1<<((x>>1)&31)))

std::vector<int> sieve;

void BitSeive()
{
    int flagArr[MAX>>6];
    std::memset(flagArr, 0, sizeof(int) * (MAX>>6));
    
    for(int i=3; i < LIM; i += 2)
        if(!ifComp(i))
            for(int j = i*i, k = i<<1; j < MAX; j += k)
                isComp(j);
       
    sieve.push_back(2);
    for(int i = 3, j = 1; i < MAX; i += 2)
        if(!ifComp(i))
            sieve.push_back(i);
}


// https://en.wikipedia.org/wiki/Fermat%27s_theorem_on_sums_of_two_squares
bool test(long n)
{
    for (auto& elem : sieve)
    { 
        if (elem * elem > n) break;
        
        int count = 0; 
        
        if (n % elem == 0) 
        { 
            while (n % elem == 0) 
            { 
                count++; 
                n /= elem; 
            }    
  
            if (elem % 4 == 3 && count % 2 != 0) 
                return false; 
        }
    } 
    
    return n % 4 != 3; 
}

int main()
{
    sieve.reserve(80000);
    BitSeive();
    
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        long num;
        std::cin >> num;
        
        if (test(num))
            std::cout << "Yes\n";
        else
            std::cout << "No\n";
    }
    
    return 0;
}
