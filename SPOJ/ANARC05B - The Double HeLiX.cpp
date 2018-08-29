/* ANARC05B - The Double HeLiX
#dynamic-programming #binary-search

Two ﬁnite, strictly increasing, integer sequences are given. Any common integer between the two sequences constitute an intersection point. Take for example the following two sequences where intersection points are
printed in bold:

    First= 3 5 7 9 20 25 30 40 55 56 57 60 62
    Second= 1 4 7 11 14 25 44 47 55 57 100

You can ‘walk” over these two sequences in the following way:

    You may start at the beginning of any of the two sequences. Now start moving forward.
    At each intersection point, you have the choice of either continuing with the same sequence you’re currently on, or switching to the other sequence.

The objective is ﬁnding a path that produces the maximum sum of data you walked over. In the above example, the largest possible sum is 450, which is the result of adding 3, 5, 7, 9, 20, 25, 44, 47, 55, 56, 57, 60, and 62
Input

Your program will be tested on a number of test cases. Each test case will be speciﬁed on two separate lines. Each line denotes a sequence and is speciﬁed using the following format:

n v1 v2 ... vn

Where n is the length of the sequence and vi is the ith element in that sequence. Each sequence will have at least one element but no more than 10,000. All elements are between -10,000 and 10,000 (inclusive).
The last line of the input includes a single zero, which is not part of the test cases.
Output

For each test case, write on a separate line, the largest possible sum that can be produced.
Sample

Input:
13 3 5 7 9 20 25 30 40 55 56 57 60 62
11 1 4 7 11 14 25 44 47 55 57 100
4 -5 100 1000 1005
3 -12 1000 1001
0

Output:
450
2100

*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>


// Solve using 2 pointers technique and binary search (std::lower_bound)
inline long solve(const std::vector<int>& vec1, 
                  const std::vector<int>& vec2)
{
    auto it1 = std::begin(vec1);
    auto it2 = std::begin(vec2);
    
    long result = 0, sum1 = 0;
    
    for (auto i = it1; i != std::end(vec1); std::advance(i, 1))
    {       
        auto tmp = std::lower_bound(it2, std::end(vec2), *i);
        
        if (*i == *tmp)
        {            
            result += std::max(sum1, std::accumulate(it2, tmp, 0L));
            
            it1 = i;
            it2 = tmp;
            sum1 = *i;
        }
        else
        {
            sum1 += *i;
        }
    }
    
    result += std::max(sum1, std::accumulate(it2, std::end(vec2), 0L));
    
    return result;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    std::vector<int> vec1, vec2;
    
    int n;
    
    while (true)
    {
        // Build vec1
        std::cin >> n;
        if (n == 0) break;
        vec1.resize(n);
        std::copy_n(std::istream_iterator<int>(std::cin), n, std::begin(vec1));
        
        // Build vec2
        std::cin >> n;
        vec2.resize(n);
        std::copy_n(std::istream_iterator<int>(std::cin), n, std::begin(vec2));
        
        // Solve
        std::cout << solve(vec1, vec2) << std::endl;
    }
    
    
    return 0;
}
