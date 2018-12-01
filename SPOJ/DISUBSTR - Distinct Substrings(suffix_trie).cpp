/*DISUBSTR - Distinct Substrings
#suffix-array-8

Given a string, we need to find the total number of its distinct substrings.
Input

T- number of test cases. T<=20;
Each test case consists of one string, whose length is <= 1000
Output

For each test case output one number saying the number of distinct substrings.
Example

Sample Input:
2
CCCCC
ABABA

Sample Output:
5
9

Explanation for the testcase with string ABABA:
len=1 : A,B
len=2 : AB,BA
len=3 : ABA,BAB
len=4 : ABAB,BABA
len=5 : ABABA
Thus, total number of distinct substrings is 9.
*/

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

class Trie {
    // A Trie node
    struct Node {
        bool isLeaf = false;
        std::unordered_map<char, std::unique_ptr<Node>> map {};
    };
    
    // Head of the trie 
    std::unique_ptr<Node> head;
    
    // Number of nodes
    std::size_t sz;
    
public:
    Trie() : head{nullptr}, sz{0} {}
    
    void insert(const std::string& str)
    {
        insert(head, str);
    }
    
    inline std::size_t size() const noexcept {return sz;}
        
private:
    // Function that returns a new Trie node
    inline std::unique_ptr<Node> getNewTrieNode()
    {
        ++sz;
        return std::make_unique<Node>();
    }
    
    // Recursive function to insert a string into the Trie.
    void insert(std::unique_ptr<Node>& head, 
                const std::string& str,
                std::size_t index = 0)
    {
        if (!head) {head = getNewTrieNode();}
        if (index == str.size()) {
            head->isLeaf = true;
            return;
        }
        else {
            if (!head->map[str[index]]) {
                head->map[str[index]] = getNewTrieNode();
            }
            insert(head->map[str[index]], str, index+1);
        }
    }
}; // end of class Trie

int main()
{
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        std::string input;
        std::cin >> input;
        
        // Create a trie of all suffixes
        Trie trie {};
        for (int i = input.size() - 1; i >= 0; --i)
            trie.insert(input.substr(i));
        
        // Result is number of nodes
        std::cout << trie.size() - 1 << std::endl;
    }
    
    return 0;
}
