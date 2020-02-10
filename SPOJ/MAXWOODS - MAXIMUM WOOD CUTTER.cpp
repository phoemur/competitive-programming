/*MAXWOODS - MAXIMUM WOOD CUTTER
#dynamic-programming

Problem Statement:


The image explains it all. You initially step at 0,0 facing right. At each step you can move according to the conditions specified in the image. You cannot step into the blocked boxes (in blue). Find the maximum number of trees you can cut.

Input:

The first line consists of an integer t, the number of test cases. For each test case the first line consists of two integers m and n, the number of rows and columns. Then follows the description of the matrix M.

M[i][j]=’T’ if the region has a tree.

M[i][j]=’#’ if the region is blocked.

M[i][j]=’0’ (zero) otherwise.

Output:

 

For each test case find the maximum trees that you can cut.

 

Input Constraints:

1<=t<=10

1<=m,n<=200

 

Example:

Sample Input:

4
5 5
0TTTT
T#T#0
#TT#T
T00T0
T0#T0
1 1
T
3 3
T#T
TTT
T#T
1 1
#

Sample Output:

8
1
3
0
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

int memo[201][201][2];

int solve(const std::vector<std::vector<char>>& vec, int x, int y, bool face_right = true)
{
    if (x >= vec.size() || x < 0 || y >= vec[0].size() || y < 0 || vec[x][y] == '#')
        return 0;
    else if (memo[x][y][face_right] != 0)
        return memo[x][y][face_right];
    else if (face_right == true)
    {
        int cur = vec[x][y] == 'T' ? 1 : 0;
        memo[x][y][face_right] = cur + std::max(solve(vec, x, y+1, true), solve(vec, x+1, y, false));
    }
    else
    {
        int cur = vec[x][y] == 'T' ? 1 : 0;
        memo[x][y][face_right] = cur + std::max(solve(vec, x, y-1, false), solve(vec, x+1, y, true));
    }
    
    return memo[x][y][face_right];
}

int main()
{
    int tests;
    std::scanf("%d", &tests);
    
    while (tests--)
    {
        std::memset(memo, 0, sizeof(int) * 201 * 201 * 2);
        
        int x, y;
        std::scanf(" %d %d", &x, &y);
        
        std::vector<std::vector<char>> vec (x, std::vector<char>(y, '0'));
        
        for (int i = 0; i < x; ++i)
            for (int j = 0; j < y; ++j)
                std::scanf(" %c", &vec[i][j]);
            
        
        std::printf("%d\n", solve(vec, 0, 0, true));
    }
    
    return 0;
}
