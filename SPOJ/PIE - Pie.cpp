/*PIE - Pie
#binary-search

My birthday is coming up and traditionally I'm serving pie. Not just one pie, no, I have a number N of them, of various tastes and of various sizes. F of my friends are coming to my party and each of them gets a piece of pie. This should be one piece of one pie, not several small pieces since that looks messy. This piece can be one whole pie though.

My friends are very annoying and if one of them gets a bigger piece than the others, they start complaining. Therefore all of them should get equally sized (but not necessarily equally shaped) pieces, even if this leads to some pie getting spoiled (which is better than spoiling the party). Of course, I want a piece of pie for myself too, and that piece should also be of the same size.

What is the largest possible piece size all of us can get? All the pies are cylindrical in shape and they all have the same height 1, but the radii of the pies can be different.
Input

One line with a positive integer: the number of test cases. Then for each test case:

    One line with two integers N and F with 1 ≤ N, F ≤ 10000: the number of pies and the number of friends.
    One line with N integers ri with 1 ≤ ri ≤ 10000: the radii of the pies. 

Output

For each test case, output one line with the largest possible volume V such that me and my friends can all get a pie piece of size V. The answer should be given as a floating point number with an absolute error of at most 10-3.
Example

Input:
3
3 3
4 3 3
1 24
5
10 5
1 4 2 3 4 5 6 5 4 2

Output:
25.1327
3.1416
50.2655

*/

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <vector>

constexpr static double PI = std::acos(-1);

int num_can_eat(const std::vector<int>& pies, double vol)
{
    int res = 0;
    
    for (auto& rad: pies)
    {
        double V = PI * rad * rad;
        res += static_cast<int>(V/vol);
    }
    
    return res;
}

double solve(const std::vector<int>& pies, int friends)
{
    double lo = 0.0001;
    double hi = PI * 10000 * 10000 * 1.0;
    
    for (int i = 0; i < 100; ++i)
    {
        double mid = (lo + hi) / 2;
        
        if (num_can_eat(pies, mid) >= friends + 1)
            lo = mid;
        else
            hi = mid;
    }
    
    return lo;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        int pies, friends;
        std::cin >> pies >> friends;
        
        std::vector<int> pie_radius (pies);
        std::copy_n(std::istream_iterator<int>(std::cin),
                    pies, 
                    std::begin(pie_radius));
        
        std::cout << std::setprecision(4) << std::fixed 
                  << solve(pie_radius, friends) << std::endl;
    }
    
    return 0;
}
