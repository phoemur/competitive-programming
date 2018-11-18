/*Zonal Computing Olympiad 2012, 26 Nov 2011

A sequence of opening and closing brackets is well-bracketed if we can pair up each opening bracket with a matching closing bracket in the usual sense. For instance, the sequences (), (()) and ()(()) are well-bracketed, while (, ()), (()(), and )( are not well-bracketed.

The nesting depth of a well-bracketed sequence tells us the maximum number of levels of inner matched brackets enclosed within outer matched brackets. For instance, the nesting depth of () and ()()() is 1, the nesting depth of (()) and ()(()) is 2, the nesting depth of ((())) is 3, and so on.

Given a well-bracketed sequence, we are interested in computing the following:

    The nesting depth, and the first position where it occurs–this will be the position of the first opening bracket at this nesting depth, where the positions are numbered starting with 1.

    The maximum number of symbols between any pair of matched brackets, including both the outer brackets, and the first position where this occurs–that is, the position of the first opening bracket of this segment


For instance, the nesting depth of ()(())()(()())(()()) is 2 and the first position where this occurs is 4. The opening bracket at position 10 is also at nesting depth 2 but we have to report the first position where this occurs, which is 4.

In this sequence, the maximum number of symbols between a pair of matched bracket is 6, starting at position 9. There is another such sequence of length 6 starting at position 15, but this is not the first such position.

Input format

The input consists of two lines. The first line is a single integer N, the length of the bracket sequence. Positions in the sequence are numbered 1,2,…,N. The second line is a sequence of N space-separated integers that encode the bracket expression as follows: 1 denotes an opening bracket ( and 2 denotes a closing bracket ). Nothing other than 1 or 2 appears in the second line of input and the corresponding expression is guaranteed to be well-bracketed.

Output format

Your program should print 4 space-separated integers in a line, denoting the four quantities asked for in the following order: nesting depth, first position that achieves the nesting depth, length of the maximum sequence between matching brackets and the first position where such a maximum length sequence occurs.

Testdata

You may assume that 2 ≤ N ≤ 105. In 30% of the test cases, 2 ≤ N ≤ 103.

    Subtask 1 (30 marks)
    Subtask 2 (70 marks)


Sample Input

20
1 2 1 1 2 2 1 2 1 1 2 1 2 2 1 1 2 1 2 2


Sample Output

2 4 6 9

*/

#include <iostream>

int main()
{
    int n;
    std::cin >> n;
    
    // Nested level and position of it
    int curr_level = 0;
    int max_level = 0;
    int idx_max = 0;
    
    // Count of symbols
    int startseq = 0, symbols = 0;
    int best_start = 0, best_symbols = 2;
    
    for (int i = 0; i < n; ++i)
    {
        int cur;
        std::cin >> cur;
        
        if (cur == 1)
            ++curr_level;
        else
            --curr_level;
        
        if (curr_level == 0) // End of the sequence
        {
            symbols = i + 1 - startseq;
            
            if (symbols > best_symbols)
            {
                best_symbols = symbols;
                best_start = startseq;
            }
            
            startseq = i+1;
        }
        
        if (curr_level > max_level)
        {
            max_level = curr_level;
            idx_max = i;
        }
    }
    
    std::cout << max_level << " " 
              << idx_max+1 << " " 
              << best_symbols << " " 
              << best_start+1 << std::endl;
    
    return 0;
}
