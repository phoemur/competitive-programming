/*ABCPATH - ABC Path
no tags 

You will be given a 2-dimensional grid of letters. Find the length of the longest path of consecutive letters, starting at 'A'. Paths can step from one letter in the grid to any adjacent letter (horizontally, vertically, or diagonally).

For example, in the following grid, there are several paths from 'A' to 'D', but none from 'A' to 'E':
ABC

One such path is:

path
Input

Each test case will start with a line contains two integers H, W the height and width of the grid respectively 1 <= H, W <= 50. Then H lines follow each of W uppercase letters only. Input terminates with H = 0 and W = 0.
Output

For each test case print “Case C: X” without quotes where C is the case number starting with 1 and X is the solution.
Example

Sample Input:
4 3
ABE
CFG
BDH
ABC
0 0

Sample Output:
Case 1: 4
*/

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

int memo[51][51];

inline bool is_valid_coord(const std::vector<std::vector<char>>& vec, int i, int j)
{
    return i < vec.size() && i >= 0 && j < vec[0].size() && j >= 0;
}

int DFS(const std::vector<std::vector<char>>& vec, int i, int j)
{
    if (memo[i][j] != 0)
        return memo[i][j];
    else
    {
        int res = 1;
    
        for (int x = i - 1; x != i + 2; ++x)
            for (int y = j - 1; y != j + 2; ++y)
                if (x != i || y != j)
                    if (is_valid_coord(vec, x, y))
                        if (vec[x][y] == vec[i][j] + 1)
                            res = std::max(res, 1 + DFS(vec, x, y));
                    
        memo[i][j] = res;
        return res;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    for (int i = 1, n, m; std::cin >> n >> m && (n != 0 || m != 0); ++i)
    {
        std::memset(memo, 0, sizeof(int) * 51 * 51);
        
        std::vector<std::vector<char>> vec (n, std::vector<char>(m, ' '));
        
        for (auto& row: vec)
            for (auto& elem: row)
                std::cin >> elem;
            
        int res = 0;
        for (int x = 0; x < n; ++x)
            for (int y = 0; y < m; ++y)
                if (vec[x][y] == 'A')
                    res = std::max(res, DFS(vec, x, y));
                
        std::cout << "Case " << i << ": " << res << std::endl;
    }
    
    return 0;
}
