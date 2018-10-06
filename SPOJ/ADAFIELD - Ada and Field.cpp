/*ADAFIELD - Ada and Field
#binary-search #datastructures

Ada the Ladybug owns a beautiful field where she grows vegetables. She often visits local Farmers Market, where she buys new seeds. Since two types of vegetable can't share same field, she always divide the field, by either vertical or horizontal line (she is very precise, so the width of line is negligible). Since she visits Farmers Market almost every day, she has already made a lot of such lines, so she needs your help with finding out the area of biggest field.
Input

The first line will contain 0 < T ≤ 200, the number of test-cases.

Then T test-cases follow, each beginning with three integers 1 ≤ N,M ≤ 2*109, 1 ≤ Q ≤ 105, top right corner of field (field goes from [0,0] to [N,M]) and number of field divisions.

Afterward Q lines follows:

0 x (0 ≤ x ≤ N), meaning that line was made vertically, on coordinate x

1 y (0 ≤ y ≤ M), meaning that line was made horizontally, on coordinate y

Sum of Q over all test-cases won't exceed 106
Output

Print Q lines, the area of biggest field after each line was made.
Example Input

2
10 10 5
0 5
0 8
1 1
1 9
1 5
10 10 5
0 5
1 4
1 6
1 8
0 5

Example Output

50
50
45
40
20
50
30
20
20
20

*/

#include <iostream>
#include <set>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        long n, m, q;
        std::cin >> n >> m >> q;
        
        std::multiset<long> xc, yc, xd, yd;
        
        xc.insert(0);
        xc.insert(n);
        yc.insert(0);
        yc.insert(m);
        xd.insert(n);
        yd.insert(m);
        
        while (q--)
        {
            int type;
            long num;
            std::cin >> type >> num;
            
            long mx, my;
            if (type == 0)
            {
                auto it1 = std::prev(xd.end());
                decltype(it1) it2;
                
                if(xc.find(num) != xc.end())
                    mx = *it1;
                else
                {
                    it1 = xc.upper_bound(num);
                    it2 = std::prev(it1);
                    long u = *it1, v = *it2;
                    it1 = xd.find(u-v);
                    xd.erase(it1);
                    xd.insert(num-v);
                    xd.insert(u-num);
                    it1 = std::prev(xd.end());
                    mx = *it1;
                }
                
                it2 = std::prev(yd.end());
                my = *it2;
                xc.insert(num);
            }
            else
            {
                auto it1 = std::prev(yd.end());
                decltype(it1) it2;
                
                if(yc.find(num) != yc.end())
                    my = *it1;
                else
                {
                    it1 = yc.upper_bound(num);
                    it2 = std::prev(it1);
                    long u = *it1, v = *it2;
                    it1 = yd.find(u-v);
                    yd.erase(it1);
                    yd.insert(num-v);
                    yd.insert(u-num);
                    it1 = std::prev(yd.end());
                    my = *it1;
                }
                
                it2 = std::prev(xd.end());
                mx = *it2;
                yc.insert(num);
            }
            
            std::cout << mx*my << std::endl;
        }
    }
        
    return 0;
}
