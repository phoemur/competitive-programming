/*NKTEAM - Team Selection
no tags 

English 	Vietnamese

The Interpeninsular Olympiad in Informatics is coming and the leaders of the Balkan Peninsula Team have to choose the best contestants on the Balkans. Fortunately, the leaders could choose the members of the team among N very good contestants, numbered from 1 to N (3 ≤ N ≤ 500000). In order to select the best contestants the leaders organized three competitions. Each of the N contestants took part in all three competitions and there were no two contestants with equal results on any of the competitions. We say that contestant А is better than another contestant В when А is ranked before В in all of the competitions. A contestant A is said to be excellent if no other contestant is better than A. The leaders of the Balkan Peninsula Team would like to know the number of excellent contestants.

Write a program, which for given N and the three competitions results, computes the number of excellent contestants.
Input

The input data are given as four lines. The first line contains the number N. The next three lines show the rankings for the three competitions. Each of these lines contains the identification numbers of the contestants, separated by single spaces, in the order of their ranking from first to last place.
Output

The output should contain one line with a single number written on it: the number of the excellent.
Example

Input
3 
2 3 1
3 1 2
1 2 3

Output
3

Note: No contestant is better than any other contestant, hence all three are excellent.

Input
10 
2 5 3 8 10 7 1 6 9 4
1 2 3 4 5 6 7 8 9 10
3 8 7 10 5 4 1 2 6 9

Output
4

Note: The excellent contestants are those numbered with 1, 2, 3 and 5.
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
    int n;
    std::scanf("%d", &n);
        
    //Clear BIT
    std::fill(BIT, BIT+n+2, std::numeric_limits<int>::max());
        
    // Input
    int curr;
    for (int i = 1; i <= n; ++i) 
    {
        std::scanf("%d", &curr);
        arr[curr-1].rank_a = i;
    }
    for (int i = 1; i <= n; ++i) 
    {
        std::scanf("%d", &curr);
        arr[curr-1].rank_b = i;
    }
    for (int i = 1; i <= n; ++i) 
    {
        std::scanf("%d", &curr);
        arr[curr-1].rank_c = i;
    }
    
    // Sort by first rank    
    std::sort(arr, arr + n);
        
    // Query and Update (INVCOUNT method)
    int excelent = 0;
    for (int i = 0; i < n; ++i)
    {
        curr = query(arr[i].rank_b);
            
        if (curr > arr[i].rank_c)
            ++excelent;
            
        update(arr[i].rank_b, arr[i].rank_c, n);
    }
       
    std::printf("%d\n", excelent);
    
    return 0;
}
