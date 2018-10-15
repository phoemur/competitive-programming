/*PKPLOL - Lord of Light
no tags 

 
**Nobel the Littlefinger** is a follower of **Lord of Light**. So he likes **7-segment display** so much because that works with LED lights.
This is a model of **7-segment display**.

Nobel the Littlefinger is a follower of Lord of Light. So he likes 7-segment display so much because that works with LED lights.

This is a model of 7-segment display.

LOL Image

And this is how it works. LOL Works

There are 7 LED light in a 7-segment Display. These are a, b, c, d,e, f, g. 

We can display any digit from 0 to 9 with these lights.

 

For example, when a, b, g, c, d lights are on that means 3 is displayed. <br/>

When a, f, e, d, c, g lights are on that means 6 is displayed. <br/>

This way 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 can be displayed with a 7-segment Display.

 

This is a very easy problem. You will be given a digit from 0 to 9 and you just have to tell the list of which lights should be on to display that digit.

 
Input

Input starts with an integer T denoting the number of test cases. Each case contains an integer N.

 
Constraints

T <= 1000

0 <=N <=9

 
Output

For each case, print the case number and the list of the lights.

You must print the list in lexicographical order in other words dictionary order. That means if a and b are a list, a must come before b. For digit  '6' the list will be acdefg, not afedcg. For digit '9' the list will be abcdfg, not acbfdg.

See the samples for further details.
Example

Input:
3
1
2
3
Output:
Case 1: bc
Case 2: abdeg
Case 3: abcdg

[ Original setter of this problem Pritom Kumar Paul, RUET ]
*/

#include <iostream>

static const char* table[10] = {"abcdef", 
                                "bc",
                                "abdeg", 
                                "abcdg", 
                                "bcfg",
                                "acdfg",
                                "acdefg",
                                "abc",
                                "abcdefg",
                                "abcdfg"};

int main()
{
    int tests;
    std::cin >> tests;
    
    for (int cas = 1; cas <= tests; ++cas)
    {
        int c;
        std::cin >> c;
        
        std::cout << "Case " << cas 
                  << ": " << table[c] 
                  << std::endl;
    }
    
    return 0;
}
