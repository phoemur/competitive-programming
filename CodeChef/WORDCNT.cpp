/*All submissions for this problem are available.

You have to submit the assignment tomorrow. It has to be 1000 words long and your lecturer has warned you about writing in really big handwriting so that you can get away with writing less. And how many words have you used?
You don't know because you have not written this program yet. Just find the number of words per line. That's it.
Input

The first line contains the number of lines of sentences. Each subsequent line contains multiple words (at least one). A ``word'' is defined as a consecutive sequence of letters (upper and/or lower case).

Your program should output a word count for each line of input.
Output

Each word count should be printed on a separate line.
Example

Input:
4
I can do this!
Yes, I will win
Code Haxor!
Taqneeq FTW!

Output:
4
4
2
2
*/

#include <algorithm>
#include <iostream>
#include <string>

int main()
{    
    std::ios_base::sync_with_stdio(false);
    
    int n;
    std::cin >> n;
    
    while (std::isspace(std::cin.peek()))
        std::cin.ignore(1);
    
    while (n--)
    {
        std::string line;
        std::getline(std::cin, line);
        
        line.erase(std::unique(std::begin(line), std::end(line)), std::end(line));
        
        std::cout << std::count_if(std::begin(line), std::end(line), ::isspace) + 1 << std::endl;
    }
    
    return 0;
}
