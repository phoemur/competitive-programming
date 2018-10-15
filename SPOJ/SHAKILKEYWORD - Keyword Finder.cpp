/*
SHAKILKEYWORD - Keyword Finder
no tags 

Nahid bhai is a principal software engineer of a renowned software company. Rumman is an associate software engineer of that company. One day Nahid bhai assigned a task to Rumman. The task is to find all keywords from a given string. A keyword is a word that contains at least one “#”. A word may contain other letters and punctuations. Given string will be split based on some delimiters. Rumman is so busy learning cutting edge technology for developing a project. So he assigned this task to you. You as a programmer will do the same thing.

For example: Given string is “Here are some fruit name: #apple, #banana, #orange.”. Delimiters are “|$ *@.&\"!^,?”. So, the words containing “#” will be: “#apple”, “#banana”, “#orange”.

Delimiters are, fixed for all string: “|$ *@.&\"!^,?”.
Input

Input starts with the number of test cases, T (1<=T<=10).

Each line contains a string consisting letters and punctuations. (1<=|string|<=100).
Output

For each test case, print the keywords in a new line. If no keywords found, then print “No keywords.”
Example

Input:

3

ab#c def#.

Abcde fghij
abc.efg#ijk #lMn.

Output:

ab#c

def#

No keywords.

efg#ijk

#lMn

*/

#include <cctype>
#include <iostream>
#include <string>
#include <vector>
   
void solve(const std::string& str)
{
    std::vector<std::string> vec;
    int pos = 0, pos2 = 0;
    
    // Split
    while (pos < str.size() && pos != std::string::npos)
    {
        pos2 = str.find_first_of(R"(|$ *@.&\"!^,?)", pos);
        vec.push_back(str.substr(pos, pos2-pos));
        pos = pos2+1;
    }
    
    // Print
    for (auto& s: vec)
        if (s.find('#') != std::string::npos)
            std::cout << s << std::endl;
}

int main()
{
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        while (std::isspace(std::cin.peek()))
            std::cin.ignore(1);
        
        std::string input;
        std::getline(std::cin, input);
        
        if (input.find('#') == std::string::npos)
            std::cout << "No keywords." << std::endl;
        else
            solve(input);
    }
    
    return 0;
}
