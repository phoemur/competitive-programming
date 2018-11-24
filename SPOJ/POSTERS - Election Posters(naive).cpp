/*POSTERS - Election Posters
#ad-hoc-1

A parliamentary election was being held in Byteland. Its enterprising and orderly citizens decided to limit the entire election campaign to a single dedicated wall, so as not to ruin the panorama with countless posters and billboards. Every politician was allowed to hang exactly one poster on the wall. All posters extend from top to bottom, but are hung at different points of the wall, and may be of different width. The wall is divided horizontally into sections, and a poster completely occupies two or more adjacent sections.

With time, some of the posters were covered (partially or completely) by those of other politicians. Knowing the location of all the posters and the order in which they were hung, determine how many posters have at least one visible section in the end.
Input

The input begins with the integer t, the number of test cases. Then t test cases follow.

Each test case begins with a line containing integer n - the number of posters (1 <= n <= 40000). Then n lines follow, the i-th (1 <= i <= n) containing exactly two integers li ri, denoting the numbers of the leftmost and rightmost sections covered by the i-th poster (1 <= li < ri <= 107). The input order corresponds to the order of hanging posters.
Output

For each test case output a line containing one integer - the number of posters with visible sections.
Example

Sample input:
1
5
1 4
2 6
8 10
3 4
7 10

Sample output:
4

An illustration of the sample input is given below.*/

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>
#include <vector>

struct Poster {
    int a;
    int b;
};
int main()
{
    int tests;
    std::scanf("%d", &tests);
    
    while (tests--)
    {
        int n;
        std::scanf("%d", &n);
        
        std::vector<int> coord; // for coord compression
        std::vector<Poster> vec (n);
        
        // Input
        for (int i = 0; i < n; ++i)
        {
            int l, r;
            std::scanf("%d %d", &l, &r);
            
            vec[i].a = l;
            vec[i].b = r;
            coord.push_back(l);
            coord.push_back(r);
        }
        
        // Transform input vec with coord compression
        std::sort(coord.begin(), coord.end());
        int mx = 0;
        
        for (auto& elem: vec)
        {
            elem.a = std::distance(std::begin(coord), std::lower_bound(coord.begin(), coord.end(), elem.a));
            elem.b = std::distance(std::begin(coord), std::lower_bound(coord.begin(), coord.end(), elem.b));
            
            if (elem.a > elem.b)
                std::swap(elem.a, elem.b);
            
            mx = std::max(mx, elem.b);
        }
        
        std::vector<int> wall (mx+1, 0);
        
        for (int i = 0; i < n; ++i)
        {
            for (int j = vec[i].a; j <= vec[i].b; ++j)
                wall[j] = i + 1;
        }
        
        std::sort(wall.begin(), wall.end());
        
        auto it = std::unique(wall.begin(), wall.end());
        auto it2 = wall.begin();
        
        while (*it2 == 0)
            std::advance(it2, 1);
        
        auto res = std::distance(it2, it);
        
        
        std::printf("%d\n", res);
    }

    return 0;
}
