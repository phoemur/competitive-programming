/*NAKANJ - Minimum Knight moves !!!
#bfs

Anjali and Nakul are good friends. They both had a quarrel recently while playing chess. Nakul wants to know the minimum number of moves a knight takes to reach from one square to another square of a chess board (8X8). Nakul is brilliant and he had already written a program to solve the problem. Nakul wants to know whether Anjali can do it. Anjali is very weak in programming. Help her to solve the problem.

A knight can move in the shape of an "L" in a chessboard - two squares either forward, backward, left, or right and then one square to its left or right. A knight move is valid if it moves as mentioned above and it is within the boundary of the chessboard (8 X 8).

knight
Input

There are T test cases in total. The next T lines contain two strings (start and destination) separated by a space.

The strings start and destination will only contain two characters - First character is an alphabet between 'a' and 'h' (inclusive), Second character is a digit between '1' and '8' (inclusive) - (Quotes just for clarity).

To know the knight moves more clearly refer to the above figure.
Output

Print the minimum number of moves a knight takes to reach from start to destination in a separate line.
Constarints

1 <= T <= 4096
Example

Input:
3
a1 h8
a1 c2
h8 c3

Output:
6
1
4

*/

#include <array>
#include <iostream>
#include <queue>
#include <vector>
#include <utility>

// Checks if board[i][j] is a valid move
inline bool isValidMove(const std::vector<std::vector<int>>& board, int i, int j)
{
    if (i < 0 || i >= static_cast<int>(board.size())) 
        return false;
    else if (j < 0 || j >= static_cast<int>(board[i].size())) 
        return false;
    else if (board[i][j] != -1) 
        return false;
    else 
        return true;
}

int solve(std::vector<std::vector<int>>& board, 
          const std::pair<int,int>& source, 
          const std::pair<int,int>& dest)
{
    static const std::array<std::pair<int,int>, 8> possible_moves {{{2 , 1}, {1 , 2}, 
                                                                    {-1, 2}, {-2, 1},
                                                                    {-2,-1}, {-1,-2},
                                                                    {1 ,-2}, {2 ,-1}}};
    
    std::queue<std::pair<int,int>> q;
    int next_i, next_j;
    
    // Start
    board[source.first][source.second] = 0;
    q.push(source);
    
    // BFS
    while (!q.empty() && board[dest.first][dest.second] == -1)
    {
        auto curr = q.front();
        q.pop();
        
        for (const auto& mv: possible_moves)
        {
            next_i = curr.first + mv.first;
            next_j = curr.second + mv.second;
            
            if (isValidMove(board, next_i, next_j))
            {
                board[next_i][next_j] = board[curr.first][curr.second] + 1;
                q.emplace(next_i, next_j);
            }
        }
    }
    
    return board[dest.first][dest.second];
}

int main()
{
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        char a, b, c, d;
        std::cin >> a >> b >> c >> d;
        
        std::vector<std::vector<int>> board (8, std::vector<int>(8, -1));
        
        auto source = std::pair<int,int>{b - '0' - 1, a - 'a'};
        auto dest   = std::pair<int,int>{d - '0' - 1, c - 'a'};
               
        std::cout << solve(board, source, dest) << std::endl;
    }
    
    return 0;
}
