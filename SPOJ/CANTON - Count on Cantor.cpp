/*CANTON - Count on Cantor
no tags 

One of the famous proofs of modern mathematics is Georg Cantor's demonstration that the set of rational numbers is enumerable. The proof works by using an explicit enumeration of rational numbers as shown in the diagram below.

1/1 1/2 1/3 1/4 1/5 ...
2/1 2/2 2/3 2/4
3/1 3/2 3/3
4/1 4/2
5/1

In the above diagram, the first term is 1/1, the second term is 1/2, the third term is 2/1, the fourth term is 3/1, the fifth term is 2/2, and so on.
Input

The input starts with a line containing a single integer t <= 20, the number of test cases. t test cases follow.

Then, it contains a single number per line.
Output

You are to write a program that will read a list of numbers in the range from 1 to 10^7 and will print for each number the corresponding term in Cantor's enumeration as given below.
Example

Input:
3
3
14
7

Output:
TERM 3 IS 2/1
TERM 14 IS 2/4
TERM 7 IS 1/4

*/

#include <iostream>

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        int t;
        std::cin >> t;
        
        for (int i = 1, res = 1; res <= t; ++i)
            for (int j = 1; j <= i && res <= t; ++j, ++res)
                if (t == res)
                    if (i % 2)
                        std::cout << "TERM " << t << " IS " << i + 1 - j << "/" << j << std::endl;
                    else
                        std::cout << "TERM " << t << " IS " << j << "/" << i + 1 - j << std::endl;
    }
    
    return 0;
}
