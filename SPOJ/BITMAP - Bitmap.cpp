/*BITMAP - Bitmap
no tags

There is given a rectangular bitmap of size n*m. Each pixel of the bitmap is either white or black, but at least one is white. The pixel in i-th line and j-th column is called the pixel (i,j). The distance between two pixels p1=(i1,j1) and p2=(i2,j2) is defined as:

d(p1,p2)=|i1-i2|+|j1-j2|.

Task

Write a program which:

    reads the description of the bitmap from the standard input,
    for each pixel, computes the distance to the nearest white pixel,
    writes the results to the standard output.

Input

The number of test cases t is in the first line of input, then t test cases follow separated by an empty line. In the first line of each test case there is a pair of integer numbers n, m separated by a single space, 1<=n <=182, 1<=m<=182. In each of the following n lines of the test case exactly one zero-one word of length m, the description of one line of the bitmap, is written. On the j-th position in the line (i+1), 1 <= i <= n, 1 <= j <= m, is '1' if, and only if the pixel (i,j) is white.
Output

In the i-th line for each test case, 1<=i<=n, there should be written m integers f(i,1),...,f(i,m) separated by single spaces, where f(i,j) is the distance from the pixel (i,j) to the nearest white pixel.
Example

Sample input:
1
3 4
0001
0011
0110

Sample output:
3 2 1 0
2 1 0 0
1 0 0 1

*/

#include <cstdio>
#include <queue>
#include <vector>

constexpr static int INF = 1 << 16;

void flood_fill(std::vector<std::vector<int>>& vec, int i, int j)
{
    const int n = vec.size();
    const int m = vec[0].size();

    std::queue<int> Q;
    Q.push(i);
    Q.push(j);

    while (!Q.empty())
    {
        int curr_x = Q.front();
        Q.pop();
        int curr_y = Q.front();
        Q.pop();

        // Test Up
        if (curr_x - 1 >= 0) // Valid coord
        {
            if (vec[curr_x-1][curr_y] > vec[curr_x][curr_y] + 1) // Relaxation is possible
            {
                vec[curr_x-1][curr_y] = vec[curr_x][curr_y] + 1;
                Q.push(curr_x-1);
                Q.push(curr_y);
            }
        }

        // Test Down
        if (curr_x + 1 < n)
        {
            if (vec[curr_x+1][curr_y] > vec[curr_x][curr_y] + 1)
            {
                vec[curr_x+1][curr_y] = vec[curr_x][curr_y] + 1;
                Q.push(curr_x+1);
                Q.push(curr_y);
            }
        }

        // Test Left
        if (curr_y - 1 >= 0)
        {
            if (vec[curr_x][curr_y-1] > vec[curr_x][curr_y] + 1)
            {
                vec[curr_x][curr_y-1] = vec[curr_x][curr_y] + 1;
                Q.push(curr_x);
                Q.push(curr_y-1);
            }
        }

        // Test Right
        if (curr_y + 1 < m)
        {
            if (vec[curr_x][curr_y+1] > vec[curr_x][curr_y] + 1)
            {
                vec[curr_x][curr_y+1] = vec[curr_x][curr_y] + 1;
                Q.push(curr_x);
                Q.push(curr_y+1);
            }
        }
    }
}

inline void solve(std::vector<std::vector<int>>& vec)
{
    for (int i = 0; i < vec.size(); ++i)
        for (int j = 0; j < vec[0].size(); ++j)
            if (vec[i][j] == 0)
                flood_fill(vec, i, j);
}

int main()
{
    int tests;
    std::scanf("%d", &tests);

    while (tests--)
    {
        int n, m;
        std::scanf("%d %d", &n, &m);

        std::vector<std::vector<int>> vec (n, std::vector<int>(m, INF));
        
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                char curr;
                std::scanf(" %c", &curr);
                if (curr == '1')
                    vec[i][j] = 0;
                else
                    vec[i][j] = INF;
            }
        }

        solve(vec);

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                std::printf("%d", vec[i][j]);

                if (j != m-1)
                    std::printf(" ");
                else
                    std::printf("\n");
            }
        }
    }

    return 0;
}
