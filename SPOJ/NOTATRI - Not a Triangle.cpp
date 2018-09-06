/*NOTATRI - Not a Triangle
#binary-search

You have N (3 ≤ N ≤ 2,000) wooden sticks, which are labeled from 1 to N. The i-th stick has a length of Li (1 ≤ Li ≤ 1,000,000). Your friend has challenged you to a simple game: you will pick three sticks at random, and if your friend can form a triangle with them (degenerate triangles included), he wins; otherwise, you win. You are not sure if your friend is trying to trick you, so you would like to determine your chances of winning by computing the number of ways you could choose three sticks (regardless of order) such that it is impossible to form a triangle with them.
Input

The input file consists of multiple test cases. Each test case starts with the single integer N, followed by a line with the integers L1, ..., LN. The input is terminated with N = 0, which should not be processed.
Output

For each test case, output a single line containing the number of triples.
Example

Input:
3
4 2 10
3
1 2 3
4
5 2 9 6
0

Output:
1
0
2

For the first test case, 4 + 2 < 10, so you will win with the one available triple. For the second case, 1 + 2 is equal to 3; since degenerate triangles are allowed, the answer is 0.
*/


#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

inline int solve(const std::vector<int>& sides)
{
    const int n = sides.size();
    int res = 0;
        
    for (int i = 0; i < n - 2; ++i) 
    {
        for (int j = i + 1; j < n - 1; ++j)
        {
            /* This will TLE, Binary search to the rescue
            for (int k = n - 1; k > j; --k)
            {
                if (sides[i] + sides[j] < sides[k])
                {
                    ++res;
                }
            }*/
                
            auto it = std::upper_bound(std::begin(sides) + j + 1, 
                                       std::end(sides), 
                                       sides[i] + sides[j]);
                
            if (it != std::end(sides))
                res += std::distance(it, std::end(sides));
        }
    }
    
    return res;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    std::vector<int> sides;
    
    for (int n; std::cin >> n && n > 0;)
    {
        sides.resize(n);
        std::copy_n(std::istream_iterator<int>(std::cin), n, std::begin(sides));
        std::sort(std::begin(sides), std::end(sides));
                
        std::cout << solve(sides) << std::endl;
    }
    
    return 0;
}
