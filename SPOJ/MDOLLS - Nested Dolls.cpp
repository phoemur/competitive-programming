/*MDOLLS - Nested Dolls

Dilworth is the world's most prominent collector of Russian nested dolls:
he literally has thousands of them! You know, the wooden hollow dolls of 
different sizes of which the smallest doll is contained in the second smallest,
and this doll is in turn contained in the next one and so forth. One day he
wonders if there is another way of nesting them so he will end up with
fewer nested dolls? After all, that would make his collection even 
more magnificent! He unpacks each nested doll and measures the width 
and height of each contained doll. A doll with width w1 and height h1 will
fit in another doll of width w2 and height h= if and only if w1 < w2 and 
h1 < h2. Can you help him calculate the smallest number of nested dolls 
possible to assemble from his massive list of measurements? 
Input
On the first line of input is a single positive integer 1 ≤ t ≤ 20 specifying
the number of test cases to follow. Each test case begins with a positive 
integer 1 ≤ m ≤ 20000 on a line of itself telling the number of dolls 
in the test case. Next follow 2m positive integers w1, h1,w2, h2, ... ,wm, 
hm, where wi is the width and hi is the height of doll number i. 
1 ≤ wi, hi ≤ 10000 for all i.

SAMPLE INPUT
4
3
20 30 40 50 30 40
4
20 30 10 10 30 20 40 50
3
10 30 20 20 30 10
4
10 10 20 30 40 50 39 51
Output
 
For each test case there should be one line of output containing the minimum
number of nested dolls possible.

SAMPLE OUTPUT
1
2
3
2*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

bool compare(const std::pair<int,int>& lhs, const std::pair<int,int>& rhs)
{
    if (lhs.first == rhs.first)
        return lhs.second > rhs.second;
    else
        return lhs.first < rhs.first;
}

int solve(const std::vector<std::pair<int,int>>& vec)
{
    const int n = vec.size();
    std::vector<std::pair<int,int>> nested;
    nested.push_back(vec[n-1]);
    
    for (int i = n-2; i >= 0; --i)
    {
        int lo = 0;
        int hi = nested.size() - 1;
        
        while (lo <= hi)
        {
            int mid = (lo + hi) / 2;
            
            if(nested[mid].first == vec[i].first || nested[mid].second <= vec[i].second)
                lo = mid+1;
            else
                hi = mid-1;
        }
        
        if (lo == nested.size())
            nested.push_back(vec[i]);
        else
            nested[lo] = vec[i];
    }
    
    return nested.size();
}

int main()
{
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        int m;
        std::cin >> m;
        
        std::vector<std::pair<int,int>> dolls (m);
        
        for (int i = 0; i < m; ++i)
            std::cin >> dolls[i].first >> dolls[i].second;
        
        std::sort(std::begin(dolls), std::end(dolls), compare);
        
        std::cout << solve(dolls) << std::endl;
    }
    
    return 0;
}
