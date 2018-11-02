/*MCIRGAME - Point Connection Game in a Circle
#number-theory #probability-theory #big-numbers #dynamic-programming #bitmasks #disjoint-set-2

English 	Vietnamese

This is a small but ancient game. You are supposed to write down the 
numbers 1, 2, 3, . . . , 2n − 1, 2n consecutively in clockwise order
on the ground to form a circle, and then, to draw some straight line
segments to connect them into number pairs. Every number must be connected
to exactly one another.
And, no two segments are allowed to intersect. It’s still a simple game, isn’t it? 
But after you’ve written down the 2n numbers, can you tell me in how
many diﬀerent ways can you connect the numbers into pairs? Life is harder, right!

Input

Each line of the input ﬁle will be a single positive number n, except 
the last line, which is a number −1.
You may assume that 1 ≤ n ≤ 150.

Sample Input
2
-1

Output

 
For each n, print in a single line the number of ways to connect the 2n
numbers into pairs.

Sample output
2

Note : Big num! */

#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

int512_t binom(unsigned int n, unsigned int k)
{
    int512_t res = 1;
 
    // Since C(n, k) = C(n, n-k)
    if (k > n - k)
        k = n - k;
 
    // Calculate value of [n*(n-1)*---*(n-k+1)] / [k*(k-1)*---*1]
    for (int i = 0; i < k; ++i) 
    {
        res *= (n - i);
        res /= (i + 1);
    }
 
    return res;
}

int512_t nth_catalan(unsigned n)
{
    return binom(2*n, n) / (n+1);
}

int main()
{
    int n;
    
    while (std::cin >> n && n != -1)
    {
        std::cout << nth_catalan(n) << std::endl;
    }
    
    return 0;
}
