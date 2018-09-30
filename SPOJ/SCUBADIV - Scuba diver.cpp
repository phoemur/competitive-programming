/*SCUBADIV - Scuba diver
#dynamic-programming

A scuba diver uses a special equipment for diving. He has a cylinder with two containers: one with oxygen and the other with nitrogen. Depending on the time he wants to stay under water and the depth of diving the scuba diver needs various amount of oxygen and nitrogen. The scuba diver has at his disposal a certain number of cylinders. Each cylinder can be described by its weight and the volume of gas it contains. In order to complete his task the scuba diver needs specific amount of oxygen and nitrogen. What is the minimal total weight of cylinders he has to take to complete the task?
Example

The scuba diver has at his disposal 5 cylinders described below. Each description consists of: volume of oxygen, volume of nitrogen (both values are given in litres) and weight of the cylinder (given in decagrams):

3 36 120
10 25 129
5 50 250
1 45 130
4 20 119

If the scuba diver needs 5 litres of oxygen and 60 litres of nitrogen then he has to take two cylinders of total weight 249 (for example the first and the second ones or the fourth and the fifth ones).
Task

Write a program that for each test case:

    reads scuba diver's demand for oxygen and nitrogen, the number of accessible cylinders and their descriptions;
    computes the minimal total weight of cylinders the scuba diver needs to complete his task;
    outputs the result.

Note: the given set of cylinders always allows to complete the given task.
Input

The number of test cases c is in the first line of input, then c test cases follow separated by an empty line.

In the first line of a test case there are two integers t, a separated by a single space, 1 <= t <= 21 and 1 <= a <= 79. They denote volumes of oxygen and nitrogen respectively, needed to complete the task. The second line contains one integer n, 1 <= n <= 1000, which is the number of accessible cylinders. The following n lines contain descriptions of cylinders; i-th line contains three integers ti, ai, wi separated by single spaces, (1 <= ti <= 21, 1 <= ai <= 79, 1 <= wi <= 800). These are respectively: volume of oxygen and nitrogen in the i-th cylinder and the weight of this cylinder.
Output

For each test case your program should output one line with the minimal total weight of cylinders the scuba diver should take to complete the task.
Example

Sample input:
1
5 60
5
3 36 120
10 25 129
5 50 250
1 45 130
4 20 119

Sample output:
249

*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

struct cylinder {
    int ox;
    int nit;
    int weight;
};

// Recurrence relation
int solve_recursive(const std::vector<cylinder>& vec, int pos, int oxig, int nitro)
{
    if (oxig <= 0 && nitro <= 0) 
        return 0;
    else if (pos == 0) 
        return std::numeric_limits<int>::max() / 100;
    else        
        return std::min(vec[pos-1].weight + solve_recursive(vec, pos-1, oxig - vec[pos-1].ox, nitro - vec[pos-1].nit), 
                        solve_recursive(vec, pos-1, oxig, nitro));
}

// Dynamic programing bottom-up approach
int solve(const std::vector<cylinder>& vec, int oxig, int nitro)
{
    const int sz = vec.size();
    
    std::vector<std::vector<std::vector<int>>> dp (sz+1, std::vector<std::vector<int>>(oxig+1, std::vector<int>(nitro+1)));
    
    // Fill table according to recurrence relation expressed above
    for (int i = 0; i <= sz; ++i)
    {
        for (int j = 0; j <= oxig; ++j)
        {
            for (int k = 0; k <= nitro; ++k)
            {
                if (j == 0 && k == 0)
                    dp[i][j][k] = 0;
                else if (i == 0)
                    dp[i][j][k] = std::numeric_limits<int>::max() / 100;
                else
                {
                    int ox_tmp  = j - vec[i-1].ox  < 0 ? 0 : j - vec[i-1].ox;
                    int nit_tmp = k - vec[i-1].nit < 0 ? 0 : k - vec[i-1].nit;
                    
                    dp[i][j][k] = std::min(vec[i-1].weight + dp[i-1][ox_tmp][nit_tmp], 
                                           dp[i-1][j][k]);
                }
            }
        }
    }
    
    return dp[sz][oxig][nitro];
}

int main()
{
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        int oxig, nitro, n;
        std::cin >> oxig >> nitro >> n;
        
        std::vector<cylinder> vec;
        vec.reserve(n);
        
        while (n--)
        {
            int a, b, c;
            std::cin >> a >> b >> c;
            vec.push_back({a, b, c});
        }
        
        //std::cout << solve_recursive(vec, vec.size(), oxig, nitro) << std::endl;
        std::cout << solve(vec, oxig, nitro) << std::endl;
    }
    
    
    return 0;
}
