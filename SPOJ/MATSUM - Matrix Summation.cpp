/*MATSUM - Matrix Summation
no tags 

A N × N matrix is filled with numbers. BuggyD is analyzing the matrix, and he wants the sum of certain submatrices every now and then, so he wants a system where he can get his results from a query. Also, the matrix is dynamic, and the value of any cell can be changed with a command in such a system.

Assume that initially, all the cells of the matrix are filled with 0. Design such a system for BuggyD. Read the input format for further details.
Input

The first line of the input contains an integer t, the number of test cases. t test cases follow.

The first line of each test case contains a single integer N (1 <= N <= 1024), denoting the size of the matrix.

A list of commands follows, which will be in one of the following three formats (quotes are for clarity):

    "SET x y num" - Set the value at cell (x, y) to num (0 <= x, y < N).
    "SUM x1 y1 x2 y2" - Find and print the sum of the values in the rectangle from (x1, y1) to (x2, y2), inclusive. You may assume that x1 <= x2 and y1 <= y2, and that the result will fit in a signed 32-bit integer.
    "END" - Indicates the end of the test case.

Output

For each test case, output one line for the answer to each "SUM" command. Print a blank line after each test case.
Example

Input:
1
4
SET 0 0 1
SUM 0 0 3 3
SET 2 2 12
SUM 2 2 2 2
SUM 2 2 3 3
SUM 0 0 2 2
END

Output:
1
12
12
13

Warning: large Input/Output data, be careful with certain languages
*/

#include <cstdio>
#include <cstring>
#include <vector>

int getSum(const std::vector<std::vector<int>>& BIT, int x, int y) 
{ 
    int sum = 0; 
  
    for (int i = x; i > 0; i -= (i & -i)) 
        for (int j = y; j > 0; j -= (j & -j)) 
            sum += BIT[i][j];
    
    return sum; 
}

void updateBIT(std::vector<std::vector<int>>& BIT, int x, int y, int val) 
{ 
    const int N = BIT.size() - 1;
    
    for (int i = x; i <= N; i += (i & -i)) 
        for (int j = y; j <= N; j += (j & -j)) 
            BIT[i][j] += val;
}

int main()
{
    int tests;
    std::scanf("%d", &tests);
    
    while (tests--)
    {
        int n;
        std::scanf("%d", &n);
        
        std::vector<std::vector<int>> BIT (n+1, std::vector<int>(n+1, 0));
        std::vector<std::vector<int>> aux (n+1, std::vector<int>(n+1, 0));
        
        while (true)
        {
            char input[30];
            int a, b, c, d;
            
            std::scanf("%s", input);
            
            if (!std::strcmp(input,"SUM"))
            {
                std::scanf("%d %d %d %d", &a, &b, &c, &d);
                ++a; ++b; ++c; ++d;
                
                int ans = 0;
                ans += getSum(BIT,   c,   d);
                ans -= getSum(BIT, a-1,   d);
                ans -= getSum(BIT,   c, b-1);
                ans += getSum(BIT, a-1, b-1);
                
                std::printf("%d\n", ans);
            }
            else if (!std::strcmp(input,"SET"))
            {
                std::scanf("%d %d %d", &a, &b, &c);
                ++a;
                ++b;

                updateBIT(BIT, a, b, -aux[a][b] + c);
                aux[a][b] = c;
            }
            else
                break;
        }
        
        
        std::printf("\n");
    }
    
    return 0;
}
