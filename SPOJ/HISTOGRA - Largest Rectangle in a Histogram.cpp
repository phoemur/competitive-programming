/*HISTOGRA - Largest Rectangle in a Histogram
#ad-hoc-1

A histogram is a polygon composed of a sequence of rectangles aligned at a common base line. The rectangles have equal widths but may have different heights. For example, the figure on the left shows the histogram that consists of rectangles with the heights 2, 1, 4, 5, 1, 3, 3, measured in units where 1 is the width of the rectangles:

Usually, histograms are used to represent discrete distributions, e.g., the frequencies of characters in texts. Note that the order of the rectangles, i.e., their heights, is important. Calculate the area of the largest rectangle in a histogram that is aligned at the common base line, too. The figure on the right shows the largest aligned rectangle for the depicted histogram.
Input Specification

The input contains several test cases. Each test case describes a histogram and starts with an integer n, denoting the number of rectangles it is composed of. You may assume that 1 <= n <= 100000. Then follow n integers h1, ..., hn, where 0 <= hi <= 1000000000. These numbers denote the heights of the rectangles of the histogram in left-to-right order. The width of each rectangle is 1. A zero follows the input for the last test case.
Output Specification

For each test case output on a single line the area of the largest rectangle in the specified histogram. Remember that this rectangle must be aligned at the common base line.
Sample Input

7 2 1 4 5 1 3 3
4 1000 1000 1000 1000
0

Sample Output

8
4000

*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <stack>
#include <vector>

// https://www.hackerrank.com/challenges/largest-rectangle/editorial
long long solve(const std::vector<long long>& vec)
{
    std::stack<int> ST;
    
    long long res = 0;
    int idx = 0;
    
    while (idx < vec.size())
    {
        if (ST.empty() || vec[idx] > vec[ST.top()])
        {
            ST.push(idx);
            ++idx;
        }
        else
        {
            auto right = vec[ST.top()];
            ST.pop();
            auto sz  = (ST.empty() ? idx : idx - ST.top() - 1);
            
            res = std::max(res, right * sz);
        }
    }
    
    return res;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
       
    for (int n; std::cin >> n && n > 0;)
    {        
        std::vector<long long> vec (n);
        std::copy_n(std::istream_iterator<long long>(std::cin), n, std::begin(vec));
        vec.push_back(0);
        
        std::cout << solve(vec) << std::endl;
    }
    
    return 0;
}
