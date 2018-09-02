/*ACODE - Alphacode
#dynamic-programming

Alice and Bob need to send secret messages to each other and are discussing ways to encode their messages:

    Alice: “Let’s just use a very simple code: We’ll assign ‘A’ the code word 1, ‘B’ will be 2, and so on down to ‘Z’ being assigned 26.”

    Bob: “That’s a stupid code, Alice. Suppose I send you the word ‘BEAN’ encoded as 25114. You could decode that in many different ways!”

    Alice: “Sure you could, but what words would you get? Other than ‘BEAN’, you’d get ‘BEAAD’, ‘YAAD’, ‘YAN’, ‘YKD’ and ‘BEKD’. I think you would be able to figure out the correct decoding. And why would you send me the word ‘BEAN’ anyway?”

    Bob: “OK, maybe that’s a bad example, but I bet you that if you got a string of length 5000 there would be tons of different decodings and with that many you would find at least two different ones that would make sense.”

    Alice: “How many different decodings?”

    Bob: “Jillions!”

For some reason, Alice is still unconvinced by Bob’s argument, so she requires a program that will determine how many decodings there can be for a given string using her code.
Input

Input will consist of multiple input sets. Each set will consist of a single line of at most 5000 digits representing a valid encryption (for example, no line will begin with a 0). There will be no spaces between the digits. An input line of ‘0’ will terminate the input and should not be processed.
Output

For each input set, output the number of possible decodings for the input string. All answers will be within the range of a 64 bit signed integer.
Example

Input:

25114
1111111111
3333333333
0

Output:

6
89
1

*/

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

// Step 1 -> Recurrence relation
std::int64_t solve_recursive(const std::string& input, int index)
{
    char c1 = input[index-1], c2 = input[index];
    
    if (index == 0)
        if (c2 == '0')
            return 0;
        else
            return 1;
    else if (index == 1)
        if (c2 == '0')
            if (c1 == '1' || c1 == '2')
                return 1;
            else 
                return 0;
        else if (c1 == '1' || (c1 == '2' && c2 <= '6'))
            return 2;
        else
            return 1;
    else
    {
        std::int64_t res = 0;

        if (c1 == '1' || (c1 == '2' && c2 <= '6'))
            res += solve_recursive(input, index-2);
        
        if (c2 != '0')
            res += solve_recursive(input, index-1);
        
        return res;
    }
}

// Step 2 -> Dynamic Programming bottom-up -> tabulation / O(n) memory
std::int64_t solve_dp(const std::string& input)
{
    const int sz = input.size();
    if (sz == 0 || input[0] == '0') return 0;
    if (sz == 1) return 1;
    
    std::vector<std::int64_t> dp (sz);
    
    // Base cases
    dp[0] = input[0] == '0' ? 0 : 1;
    if (input[1] == '0')
        if (input[0] == '1' || input[0] == '2')
            dp[1] = 1;
        else
            dp[1] = 0;
    else if (input[0] == '1' || (input[0] == '2' && input[1] <= '6'))
        dp[1] = 2;
    else
        dp[1] = 1;
    
    // Fill table
    for (int i = 2; i < sz; ++i)
    {
        char c1 = input[i-1], c2 = input[i];
        dp[i] = 0;
        
        if (c1 == '1' || (c1 == '2' && c2 <= '6'))
            dp[i] += dp[i-2];
        
        if (c2 != '0')
            dp[i] += dp[i-1];
    }
    
    return dp.back();
}

// Step 3 -> Dynamic Programming bottom-up -> tabulation and O(1) memory
std::int64_t solve_dp_optimized(const std::string& input)
{
    const int sz = input.size();
    if (sz == 0 || input[0] == '0') return 0;
    if (sz == 1) return 1;
    
    std::int64_t curr, last, tmp;
    
    // Base cases
    last = input[0] == '0' ? 0 : 1;
    if (input[1] == '0')
        if (input[0] == '1' || input[0] == '2')
            curr = 1;
        else
            curr = 0;
    else if (input[0] == '1' || (input[0] == '2' && input[1] <= '6'))
        curr = 2;
    else
        curr = 1;
    
    // Fill
    for (int i = 2; i < sz; ++i)
    {
        char c1 = input[i-1], c2 = input[i];
        tmp = 0;
        
        if (c1 == '1' || (c1 == '2' && c2 <= '6'))
            tmp += last;
        
        if (c2 != '0')
            tmp += curr;
        
        last = curr;
        curr = tmp;
    }
    
    return curr;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    std::string input;
    
    while (std::getline(std::cin, input) && input != "0")
    {
        //std::cout << solve_recursive(input, input.size() - 1) << std::endl;
        //std::cout << solve_dp(input) << std::endl;
        std::cout << solve_dp_optimized(input) << std::endl;
    }
    
    return 0;
}
