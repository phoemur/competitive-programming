/*NY10E - Non-Decreasing Digits
#dynamic-programming

A number is said to be made up of non-decreasing digits if all the digits to the left of any digit is less than or equal to that digit.For example, the four-digit number 1234 is composed of digits that are non-decreasing.  Some other four-digit numbers that are composed of non-decreasing digits are 0011, 1111, 1112, 1122, 2223.  As it turns out, there are exactly 715 four-digit numbers composed of non-decreasing digits.
 
Notice that leading zeroes are required: 0000, 0001, 0002 are all valid four-digit numbers with non-decreasing digits.
 
For this problem, you will write a program that determines how many such numbers there are with a specified number of digits.
Input

The first line of input contains a single integer P, (1 ≤ P ≤ 1000), which is the number of data sets that follow.  Each data set is a single line that contains the data set number, followed by a space, followed by a decimal integer giving the number of digits N, (1 ≤ N ≤ 64).
Output

For each data set there is one line of output.  It contains the data set number followed by a single space, followed by the number of N digit values that are composed entirely of non-decreasing digits.

Example

Input:
3
1 2
2 3
3 4

Output:
1 55
2 220
3 715*/

#include <bits/stdc++.h>

long long dp[74][10];

// https://oeis.org/A000582
int main()
{
    std::memset(dp, 0, sizeof(dp));
    
    // Fill dp for binomial coeficients
    for (int i = 0; i < 74; i++) 
        for (int j = 0; j <= std::min(i, 9); j++) 
            if (j == 0 || j == i) 
                dp[i][j] = 1; 
            else
                dp[i][j] = dp[i-1][j-1] + dp[i-1][j]; 
    
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        int a, b;
        std::cin >> a >> b;
        
        std::cout << a << " " << dp[b+9][9] << std::endl;
    }
        
    return 0;
}
