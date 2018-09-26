/*SKYLINE - Skyline
no tags 

The director of a new movie needs to create a scaled set for the movie. In the set there will be N skyscrapers, with distinct integer heights from 1 to N meters. The skyline will be determined by the sequence of the heights of the skyscrapers from left to right. It will be a permutation of the integers from 1 to N.

The director is extremely meticulous, so she wants to avoid a certain sloping pattern. She doesn’t want for there to be ANY three buildings in positions i, j and k, i < j < k, where the height of building i is smaller than that of building j, and building j’s height is smaller than building k’s height.

Your task is to tell the director, for a given number of buildings, how many distinct orderings for the skyline avoid the sloping pattern she doesn't like.
Input

There will be several test cases in the input. Each test case will consist of a single line containing a single integer N (3 ≤ N ≤ 1,000), which represents the number of skyscrapers. The heights of the skyscrapers are assumed to be 1, 2, 3, ..., N. The input will end with a line with a single 0.
Output

For each test case, output a single integer, representing the number of good skylines - those avoid the sloping pattern that the director dislikes - modulo 1,000,000. Print each integer on its own line with no spaces. Do not print any blank lines between answers.
Example

Input:
3
4
0

Output:
5
14*/

#include <iostream>
#include <vector>

inline std::vector<long> catalan()
{
    std::vector<long> res (1002);
    
    res[0] = res[1] = 1;
    
    for (int i = 2; i < 1002; ++i)
    {
        res[i] = 0;
        for (int j = 0; j < i; ++j)
            res[i] += (res[j] * res[i-j-1]) % 1000000;
    
        res[i] %= 1000000;
    }
    
    return res;
}

int main()
{
    auto vec = catalan();
    
    for (int n; std::cin >> n && n != 0;)
    {
        std::cout << vec[n] << std::endl;
    }
    
    return 0;
}
