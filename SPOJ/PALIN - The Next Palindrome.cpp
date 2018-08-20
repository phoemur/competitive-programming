/*PALIN - The Next Palindrome
#ad-hoc-1

A positive integer is called a palindrome if its representation in the decimal system is the same when read from left to right and from right to left. For a given positive integer K of not more than 1000000 digits, write the value of the smallest palindrome larger than K to output. Numbers are always displayed without leading zeros.
Input

The first line contains integer t, the number of test cases. Integers K are given in the next t lines.
Output

For each K, output the smallest palindrome larger than K.
Example

Input:
2
808
2133

Output:
818
2222

Warning: large Input/Output data, be careful with certain languages
*/

#include <algorithm>
#include <iostream>
#include <string>

inline void mirror(std::string& str)
{ 
    std::copy(str.rbegin() + str.size() / 2, 
              str.rend(), 
              str.begin() + str.size() / 2);
}

inline void fix(std::string& str, int pos1, int pos2)
{
    if (pos1 < 0) {
        str.back() = '1';
        str.insert(0, 1, '1');
    } else if (str[pos1] < '9') {
        str[pos1] = str[pos2] = str[pos1] + 1;
    } else {
        str[pos1] = str[pos2] = '0';
        fix(str, pos1-1, pos2+1);
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        std::string input;
        std::cin >> input;
        std::string tmp (input);
        
        mirror(tmp);
        
        if (tmp <= input)
            fix(tmp, (tmp.size()-1) / 2, tmp.size() / 2);
            
        std::cout << tmp << std::endl;
    }
    
    return 0;
}
