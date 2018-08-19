/*TSORT - Turbo Sort
no tags 

Given the list of numbers, you are to sort them in non decreasing order.
Input

t – the number of numbers in list, then t lines follow [t <= 10^6].
Each line contains one integer: N [0 <= N <= 10^6]
Output

Output given numbers in non decreasing order.
Example

Input:

5
5
3
6
7
1

Output:

1
3
5
6
7

*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

template<typename ForwardIterator>
void countingSort(ForwardIterator first, 
                  ForwardIterator last, 
                  int Beg, 
                  int End)
{    
    assert(End - Beg >= 0);
    
    std::vector<int> counts (End - Beg + 1, 0);

    // Count
    for (auto it = first; it != last; std::advance(it, 1)) {
        ++counts[*it - Beg];
    }

    // Store in sorted order
    for (int i=0; i < counts.size(); ++i) {
        first = std::fill_n(first, counts[i], i + Beg);
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int mx = std::numeric_limits<int>::min();
    int mn = std::numeric_limits<int>::max();
    
    int n, tmp;
    std::cin >> n;
    
    std::vector<int> table;
    table.reserve(n);
    
    while (n--) {
        std::cin >> tmp;
        table.push_back(tmp);
        
        mx = std::max(mx, tmp);
        mn = std::min(mn, tmp);
    }
    
    countingSort(table.begin(), table.end(), mn, mx);
    
    for (auto& n: table) std::cout << n << "\n";
    
    return 0;
}
