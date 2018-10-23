/*YODANESS - Yodaness Level
#graph-theory #number-theory #shortest-path #sorting #tree #bitmasks

Yoda is the wisest, and perhaps the most powerful Jedi of his time. Yoda is a mysterious figure and he has many oddities. One of them is that Yoda often changes the order of words in the sentence. For example, one of such phrases is "Or I will help you not." Let's call the yodaness level of any statement the number of pairs of words that changed their order, as to the order in which they were supposed to go in a normal statement. Write a program that determines the yodaness level of different statement of Yoda.
 
Input

The first line of input contains the number t - the number of tests. Next comes the description of t tests. Each test consists of three rows. The first line of the test contains an integer n - number of words in the statement. The next line contains n words separated by spaces - the statement as Yoda says it. The next line is n words separated by spaces - the same statement as it should be said normally. All the words in the statement are different and consist of small latin letters.
Constraints

1 <= t <= 10
1 <= n <= 30000
the length of each word does not exceed 20 characters
Output

For each test print the yodaness level of the statement.
Example

Input:
2
6
in the force strong you are
you are strong in the force
6
or i will help you not
or i will not help you

Output:
11
2

*/

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#include <unordered_map>

#define MAX 30003

int BIT[MAX];

void update_bit(int pos)
{
    while (pos <= MAX)
    {
        BIT[pos]++;
        pos += (pos & -pos);
    }
}

int query_bit(int pos)
{
    int sum = 0;
    
    while (pos > 0)
    {
        sum += BIT[pos];
        pos -= (pos & -pos);
    }
    
    return sum;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        std::unordered_map<std::string,int> table; // Map string to int
        
        std::memset(BIT, 0, sizeof(int) * MAX);
        
        int words;
        std::cin >> words;
        
        for (int i = 1; i <= words; ++i)
        {
            std::string input;
            std::cin >> input;
            
            if (table.find(input) == table.end())
                table[input] = i;
        }
        
        std::vector<std::pair<int,int>> arr; // Pair Value, index
        arr.reserve(words);
        
        for (int i = 1; i <= words; ++i)
        {
            std::string input;
            std::cin >> input;
            
            arr.emplace_back(table[input], i);
        }
        
        std::sort(arr.rbegin(), arr.rend());
        
        int res = 0;
        for (int i = 0; i < words; ++i)
        {
            res += query_bit(arr[i].second);
            update_bit(arr[i].second);
        }
        
        std::cout << res << std::endl;
    }
    
    return 0;
}
