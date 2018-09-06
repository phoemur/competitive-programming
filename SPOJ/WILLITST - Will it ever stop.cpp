/*WILLITST - Will it ever stop
#ad-hoc-1

When Bob was in library in University of Warsaw he saw on one of facades caption :"Will it ever stop?" and below some mysterious code:

while n > 1
  if n mod 2 = 0 then
    n:=n/2
  else
    n:=3*n+3

Help him finding it out !

Input

In first line one number n<=10^14.
Output

Print "TAK" if program will stop, otherwise print "NIE"
Example

Input:
4

Output:
TAK

*/

#include <iostream>

int main()
{
    long long n;
    std::cin >> n;

    while (n > 1)
    {
        if (n % 2 == 0)
            n /= 2;
        else
        {
            std::cout << "NIE" << std::endl;
            return 0;
        }
            
    }
    
    std::cout << "TAK" << std::endl;
    
    return 0;
}
