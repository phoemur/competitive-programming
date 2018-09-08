/*ADFRUITS - Advanced Fruits
#lcs #dynamic-programming #backtracking

The company "21st Century Fruits" has specialized in creating new sorts of fruits by transferring genes from one fruit into the genome of another one. Most times this method doesn't work, but sometimes, in very rare cases, a new fruit emerges that tastes like a mixture between both of them.

A big topic of discussion inside the company is "How should the new creations be called?" A mixture between an apple and a pear could be called an apple-pear, of course, but this doesn't sound very interesting. The boss finally decides to use the shortest string that contains both names of the original fruits as sub-strings as the new name. For instance, "applear" contains "apple" and "pear" (APPLEar and apPlEAR), and there is no shorter string that has the same property.
A combination of a cranberry and a boysenberry would therefore be called a "boysecranberry" or a "craboysenberry", for example.

Your job is to write a program that computes such a shortest name for a combination of two given fruits. Your algorithm should be efficient, otherwise it is unlikely that it will execute in the alloted time for long fruit names.
Input Specification

Each line of the input file contains two strings that represent the names of the fruits that should be combined. All names have a maximum length of 100 and only consist of alphabetic characters.
Input is terminated by end of file.
Output Specification

For each test case, output the shortest name of the resulting fruit on one line. If more than one shortest name is possible, any one is acceptable.
Sample Input

apple peach
ananas banana
pear peach

Sample Output

appleach
bananas
pearch

*/

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Recurrence relation for Shortest Common Supersequence
// https://www.geeksforgeeks.org/shortest-common-supersequence/
int SCS_recursive(const std::string& str1, int pos1, const std::string& str2, int pos2) 
{
    if (pos1 == 0) return pos2; 
    else if (pos2 == 0) return pos1; 
    else if (str1[pos1-1] == str2[pos2-1]) 
        return 1 + SCS_recursive(str1, pos1 - 1, str2, pos2 - 1); 
    else
        return 1 + std::min(SCS_recursive(str1, pos1 - 1, str2, pos2), 
                            SCS_recursive(str1, pos1, str2, pos2 - 1)); 
} 

std::string solve(const std::string& str1, const std::string& str2)
{
    int sz1 = str1.size(), sz2 = str2.size();
    
    // Fill dynamic programming table bottom-up according to the recurrence expressed above
    std::vector<std::vector<int>> dp (sz1 + 1, std::vector<int>(sz2 + 1));
    
    for (int i = 0; i <= sz1; ++i)
    {
        for (int j = 0; j <= sz2; ++j)
        {
            if (i == 0)
                dp[i][j] = j;
            else if (j == 0)
                dp[i][j] = i;
            else if (str1[i-1] == str2[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                dp[i][j] = 1 + std::min(dp[i][j-1], dp[i-1][j]);
        }
    }
       
    // Use it to find the Shortest Common Supersequence
    int index = dp[sz1][sz2];
    std::string res (index, ' ');
    
    while (sz1 > 0 && sz2 > 0)
    {
        if (str1[sz1-1] == str2[sz2-1])
        {
            res[index-1] = str1[sz1-1];
            --sz1;
            --sz2;
            --index;
        }
        
        // If not same, then find the larger of two and
        // go in the direction of larger value
        else if (dp[sz1-1][sz2] < dp[sz1][sz2-1])
        {
            res[index-1] = str1[sz1-1];
            --sz1;
            --index;
        }
        else
        {
            res[index-1] = str2[sz2-1];
            --sz2;
            --index;
        }
    }
    
    // Copy remaining characters of string 'str1' 
    while (sz1 > 0) 
    { 
        res[index-1] = str1[sz1-1];
        --sz1;
        --index;
    }  

    // Copy remaining characters of string 'str2' 
    while (sz2 > 0) 
    { 
        res[index-1] = str2[sz2-1];
        --sz2;
        --index;
    }    
    
    return res;
}

int main()
{    
    for (std::string input; std::getline(std::cin, input) && input.size() > 0;)
    {
        std::istringstream ss {input};
        std::string a, b;
        
        if (ss >> a >> b)
            std::cout << solve(a, b) << std::endl;
    }
    
    return 0;
}
