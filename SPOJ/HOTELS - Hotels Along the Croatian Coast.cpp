/*HOTELS - Hotels Along the Croatian Coast
#sliding-window-1

There are N hotels along the beautiful Adriatic coast. Each hotel has its value in Euros.

Sroljo has won M Euros on the lottery. Now he wants to buy a sequence of consecutive hotels, such that the sum of the values of these consecutive hotels is as great as possible - but not greater than M.

You are to calculate this greatest possible total value.
Input

In the first line of the input there are integers N and M (1 ≤ N ≤ 300 000, 1 ≤ M < 231).

In the next line there are N natural numbers less than 106, representing the hotel values in the order they lie along the coast.
Output

Print the required number (it will be greater than 0 in all of the test data).
Example
input

5 12
2 1 3 4 5

output
12

input

4 9
7 3 5 6

output
8
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    int n, m;
    std::cin >> n >> m;
    
    std::vector<int> vec (n);
    std::copy_n(std::istream_iterator<int>(std::cin), n, std::begin(vec));
    
    auto slow = std::begin(vec);
    auto fast = std::begin(vec);
    int sum = 0, best = 0;
    
    while (slow != std::end(vec))
    {
        while (fast != std::end(vec) && sum + (*fast) <= m)
        {
            sum += *fast;
            std::advance(fast, 1);
        }
        
        best = std::max(best, sum);
        
        sum -= *slow;
        std::advance(slow, 1);
    }
    
    std::cout << best << std::endl;
    
    return 0;
}
