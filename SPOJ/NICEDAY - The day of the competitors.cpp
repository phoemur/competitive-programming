/*NICEDAY - The day of the competitors
#tree

The International Olympiad in Informatics is coming and the leaders of the Vietnamese Team have to choose the best contestants all over the country. Fortunately, the leaders could choose the members of the team among N very good contestants, numbered from 1 to N (3 ≤ N ≤ 100000). In order to select the best contestants the leaders organized three competitions. Each of the N contestants took part in all three competitions and there were no two contestants with equal results on any of the competitions. We say that contestant А is better than another contestant В when А is ranked before В in all of the competitions. A contestant A is said to be excellent if no other contestant is better than A. The leaders of the Vietnamese Team would like to know the number of excellent contestants.
Input

First line of the input contains an integer t (1 ≤ t ≤ 10 ), equal to the number of testcases. Then descriptions of t testcases follow. First line of description contains the number of competitors N . Each of the next N lines describes one competitor and contains integer numbers ai, bi, ci (1 ≤ ai, bi , ci ≤ N ) separated by spaces, the order of i-th competitor's ranking in the first competition , the second competition and the third competition.
Output

For each test case in the input your program should output the number of excellent contestants in one line.

Note: Because the input is too large so we have 4 input files and the total time limit is 4s ( not 1s ).
Example

Input:
1
3
1 2 3
2 3 1
3 1 2

Output:
3

*/

#include <algorithm>
#include <cstdio>
#include <limits>

struct Contestant {
    int rank_a;
    int rank_b;
    int rank_c;
};

// Sort only by the first rank
bool operator<(const Contestant& lhs, const Contestant& rhs)
{
    return lhs.rank_a < rhs.rank_a;
}

Contestant arr[100002];
int        BIT[100002];


void update(int idx, int value, int n) 
{
    while (idx <= n) 
    {
        BIT[idx] = std::min(BIT[idx], value);
        idx += (idx & -idx);
    }
}

int query(int idx)
{
    int res = std::numeric_limits<int>::max();
    
    while (idx > 0)
    {
        res = std::min(res, BIT[idx]);
        idx -= (idx & -idx);
    }
    
    return res;
}

int main()
{
    int tests;
    std::scanf("%d", &tests);
    
    while (tests--)
    {
        int n;
        std::scanf("%d", &n);
        
        //Clear BIT
        std::fill(BIT, BIT+n+2, std::numeric_limits<int>::max());
        
        // Input
        for (int i = 0; i < n; ++i)
            std::scanf("%d %d %d", 
                       &arr[i].rank_a, 
                       &arr[i].rank_b, 
                       &arr[i].rank_c);
        
        // Sort by first rank    
        std::sort(arr, arr + n);
        
        // Query and Update (INVCOUNT method)
        int excelent = 0;
        for (int i = 0; i < n; ++i)
        {
            int curr = query(arr[i].rank_b);
            
            if (curr > arr[i].rank_c)
                ++excelent;
            
            update(arr[i].rank_b, arr[i].rank_c, n);
        }
        
        std::printf("%d\n", excelent);
    }
    
    return 0;
}
