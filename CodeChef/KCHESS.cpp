/*All submissions for this problem are available.Abhineet the Chess master of NIT Kurukshetra got bored of 8x8 chess board and invented the new variation of Chess, the one on an infinite chess board. There is only a white king and N

black knights. The white king has to avoid checkmate as long as it can.

A situation is given. Determine if white king is in checkmate or not. The white king is in checkmate if and only if it is in check and it is not able to move to any of its neighboring positions which is not in check.
Input:

    The first line will contain T

, number of test cases. Then the test cases follow.
The first line of each test case contains a single integer N
.
The next N line contains 2 space-separated integers Xi
and Yi
denoting the position of knights.
The next line contains 2 space-separated integers A
and B

    denoting the position of king

Output:

Print a single line corresponding to each test case — “YES” (without quotes) – if the king is in checkmate and “NO” (without quotes) – if the king is not in checkmate.
Constraints

    1≤T≤5

1≤N≤105
−109≤Xi,Yi,A,B≤109

Sample Input:

2
6
1 0
0 2
2 5
4 4
5 0
6 2
3 2
4
5 6
3 5
2 8
-8 -8
0 0

Sample Output:

YES

NO
EXPLANATION:

In the first test case, the king is in cannot move to any valid position In second test case, the king can easily make a valid move.*/

#include <algorithm>
#include <array>
#include <cstdio>
#include <vector>
#include <utility>

static const std::array<std::pair<int,int>, 8> knight_moves {{{2 , 1}, {1 , 2}, 
                                                              {-1, 2}, {-2, 1},
                                                              {-2,-1}, {-1,-2},
                                                              {1 ,-2}, {2 ,-1}}};
                                                              
static const std::array<std::pair<int,int>, 8> king_moves {{{-1,-1}, {-1,0}, {-1,1},
                                                            {0, -1},         {0, 1},
                                                            {1, -1}, {1, 0}, {1, 1}}};                                                              

// Checks if board[i][j] is a valid move
inline bool is_valid_move(const std::vector<std::vector<char>>& board, int i, int j)
{
    if (i < 0 || i >= static_cast<int>(board.size())) 
        return false;
    else if (j < 0 || j >= static_cast<int>(board[i].size())) 
        return false;
    else 
        return true;
}

// Checks if board[i][j] is under attack by a knight
inline bool is_under_attack(const std::vector<std::vector<char>>& board, int i, int j)
{
    for (auto& p: knight_moves)
    {
        int next_i = i + p.first;
        int next_j = j + p.second;
        
        if (is_valid_move(board, next_i, next_j))
        {
            if (board[next_i][next_j] == 'k')
            {
                return true;
            }
        }
    }
    
    return false;
}

// Checks if the king at board[king_x][king_y] is under checkmate
bool is_checkmate(const std::vector<std::vector<char>>&  board, int king_x, int king_y)
{
    if (!is_under_attack(board, king_x, king_y))
        return false;
    else
    {
        for (auto& p: king_moves)
        {
            int next_i = king_x + p.first;
            int next_j = king_y + p.second;
            
            if (is_valid_move(board, next_i, next_j) && board[next_i][next_j] == ' ')
            {
                if (!is_under_attack(board, next_i, next_j))
                {
                    return false;
                }
            }
        }
        
        return true;
    }
}

int main()
{
    int tests;
    std::scanf("%d", &tests);
    
    while (tests--)
    {
        int n;
        std::scanf("%d", &n);
        
        // Normalize inputs
        std::vector<std::pair<int,int>> positions;
        positions.reserve(n+1);
              
        for (int i = 0; i <= n; ++i) // King goes last
        {
            int a, b;
            std::scanf("%d %d", &a, &b);
            
            positions.emplace_back(a, b);
        }
        
        // Create 7x7 Board with king at the center
        std::vector<std::vector<char>> board (7, std::vector<char>(7, ' '));
        board[3][3] = 'K';
        
        // King offset
        std::pair<int,int> king = positions.back();
        positions.pop_back();
        
        // Place Knights
        for (auto& p: positions)
            if (is_valid_move(board, king.first - p.first + 3, king.second - p.second + 3))
                board[king.first - p.first + 3][king.second - p.second + 3] = 'k';
                   
        // Solve
        if (is_checkmate(board, 3, 3))
            std::printf("YES\n");
        else
            std::printf("NO\n");
    }
    
    return 0;
}
