/*ABCDEF - ABCDEF
#binary-search

You are given a set S of integers between -30000 and 30000 (inclusive).

Find the total number of sextuples  that satisfy: 

 
Input

The first line contains integer N (1 ≤ N ≤ 100), the size of a set S.

Elements of S are given in the next N lines, one integer per line. Given numbers will be distinct.
Output

Output the total number of plausible sextuples.
Examples

Input:
1
1

Output:
1

	

Input:
2
2
3

Output:
4

	

Input:
2
-1
1

Output:
24

	

Input:
3
5
7
10

Output:
10


*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int n;
    std::cin >> n;
    
    std::vector<int> vec (n);
    std::copy_n(std::istream_iterator<int>(std::cin), n, std::begin(vec));
    
    std::vector<int> s1, s2;
    s1.reserve(n*n*n);
    s2.reserve(n*n*n);
    
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                s1.push_back(vec[i]*vec[j]+vec[k]);
            
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                if (vec[k] != 0)
                    s2.push_back((vec[i]+vec[j])*vec[k]);
            
    
    std::sort(std::begin(s2), std::end(s2));
    
    int res = 0;
    
    for (auto& lhs: s1)
    {
        auto rhs = std::equal_range(std::begin(s2), std::end(s2), lhs);
        res += std::distance(rhs.first, rhs.second);
    }
    
    std::cout << res << std::endl;
    
    return 0;
}
