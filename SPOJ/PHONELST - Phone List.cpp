/*PHONELST - Phone List
no tags 

Phone List

Given a list of phone numbers, determine if it is consistent in the sense that no number is the prefix of another. Let’s say the phone catalogue listed these numbers:

    Emergency 911
    Alice 97 625 999
    Bob 91 12 54 26

In this case, it’s not possible to call Bob, because the central would direct your call to the emergency line as soon as you had dialled the first three digits of Bob’s phone number. So this list would not be consistent.
Input

The first line of input gives a single integer, 1 <= t <= 40, the number of test cases. Each test case starts with n, the number of phone numbers, on a separate line, 1 <= n <= 10000. Then follows n lines with one unique phone number on each line. A phone number is a sequence of at most ten digits.
Output

For each test case, output “YES” if the list is consistent, or “NO” otherwise.
Example

Input:
2
3
911
97625999
91125426
5
113
12340
123440
12345
98346

Output:
NO
YES

*/

#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <string>

class Trie {
    
    // A Trie node
    struct Node {
        bool isLeaf = false;
        std::array<std::unique_ptr<Node>, 10> children {nullptr};
    };
    
    // Head of the trie 
    std::unique_ptr<Node> head {nullptr};
    
public:
        
    void insert(const std::string& str)
    {
        insert(head, str);
    }    
        
    bool consistent() const noexcept
    {
        return consistent(head);
    }

private:
    // Function that returns a new Trie node
    inline std::unique_ptr<Node> getNewTrieNode()
    {
        return std::make_unique<Node>();
    }
    
    // Recursive function to insert a string in Trie.
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
            if (head->children.at(str[index] - '0') == nullptr) {
                head->children[str[index] - '0'] = getNewTrieNode();
            }
            insert(head->children[str[index] - '0'], str, index+1);
        }
    }
    
    bool haveChildren(const std::unique_ptr<Node>& curr) const noexcept
    {
        return std::any_of(std::begin(curr->children), 
                           std::end(curr->children), 
                           [](const auto& a) 
                           {
                               return a != nullptr;
                           });
    }
    
    bool consistent(const std::unique_ptr<Node>& curr) const noexcept
    {
        if (curr == nullptr) 
            return true;
        else if (curr->isLeaf && haveChildren(curr)) 
            return false;
        else
        {
            for (const auto& node: curr->children)
                if (node != nullptr)
                    if (!consistent(node))
                        return false;
                    
            return true;
        }
    }
    
}; // end of class Trie

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        int n;
        std::cin >> n;
        
        Trie trie {};
        
        while (n--)
        {
            std::string input;
            std::cin >> input;
            
            trie.insert(input);
        }
        
        if (trie.consistent())
            std::cout << "YES" << std::endl;
        else
            std::cout << "NO" << std::endl;
    }
    
    return 0;
}
