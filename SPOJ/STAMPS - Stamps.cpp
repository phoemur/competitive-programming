/*STAMPS - Stamps
#ad-hoc-1

Everybody hates Raymond. He’s the largest stamp collector on planet earth and because of that he always makes fun of all the others at the stamp collector parties. Fortunately everybody loves Lucy, and she has a plan. She secretly asks her friends whether they could lend her some stamps, so that she can embarrass Raymond by showing an even larger collection than his. Raymond is so sure about his superiority that he always tells how many stamps he’ll show.And since Lucy knows how many she owns, she knows how many more she needs. She also knows how many friends would lend her some stamps and how many each would lend. But she’s like to borrow from as few friends as possible and if she needs too many then she’d rather not do it at all. Can you tell her the minimum number of friends she needs to borrow from?
Input

The first line contains the number of scenarios. Each scenario describes one collectors party and its first line tells you how many stamps (from 1 to 1000000) Lucy needs to borrow and how many friends (from 1 to 1000) offer her some stamps. In a second line you’ll get the number of stamps (from 1 to 10000) each of her friends id offering.
Output

The output for every scenario begins with a line containing “Scenario #i:”, where i is the number of the scenario starting at 1. Then print a single line with the minimum number of friends Lucy needs to borrow stamps from. If it’s impossible even if she borrows everything from everybody, write impossible. Terminate the output for the scenario with a blank line.
Example

Input:
3
100 6
13 17 42 9 23 57
99 6
13 17 42 9 23 57
1000 3
314 159 265


Output:
Scenario #1:
3

Scenario #2:
2

Scenario #3:
impossible

*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    int scen;
    std::cin >> scen;
    
    for (int i = 1; i <= scen; ++i)
    {
        int n, t;
        std::cin >> n >> t;
        
        std::vector<int> stamps (t);
        std::copy_n(std::istream_iterator<int>(std::cin), t, std::begin(stamps));
        std::sort(stamps.rbegin(), stamps.rend());
        
        int sum = 0;
        for (int friends = 0; friends < stamps.size(); ++friends)
        {
            sum += stamps[friends];
            
            if (sum >= n)
            {
                std::cout << "Scenario #" << i << ":\n" << friends + 1 << "\n\n";
                break;
            }
        }
        
        if (sum < n)
            std::cout << "Scenario #" << i << ":\nimpossible\n\n";
    }
    
    return 0;
}

/* 2nd version - worse big-O complexity
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

int main()
{
    int scen;
    std::cin >> scen;
    
    for (int i = 1; i <= scen; ++i)
    {
        int n, t;
        std::cin >> n >> t;
        
        // Input stamps and sort
        std::vector<long> stamps (t);
        std::copy_n(std::istream_iterator<long>(std::cin), t, std::begin(stamps));
        std::sort(stamps.rbegin(), stamps.rend());
        
        // Build preffix sum
        std::vector<long> preffix_sum (t);
        std::partial_sum(std::begin(stamps), std::end(stamps), std::begin(preffix_sum));
        
        // Binary search
        auto it = std::lower_bound(std::begin(preffix_sum), std::end(preffix_sum), n);
        
        if (it != std::end(preffix_sum))
            std::cout << "Scenario #" << i << ":\n" << std::distance(std::begin(preffix_sum), it) + 1 << "\n\n";
        else
            std::cout << "Scenario #" << i << ":\nimpossible\n\n";
        
    }
    
    return 0;
}
*/
