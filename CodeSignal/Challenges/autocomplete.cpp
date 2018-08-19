/*Hey, we all use text editors all the time right? This is another fun challenge based on the algorithmic ideas behind text editors!

This time we'll be looking at autocomplete - a feature commonly found in development environments, search engines, and smartphones. If the user pauses while typing out a word, autocomplete will suggest possible words beginning with the characters they've typed.

Given a list of words and a series of actions (keystrokes or pauses), we'd like to produce an array of suggested words for every time we encounter a pause (sorted lexicographically).

Since it can be frustrating to work with key codes, the input is given as an array of strings (any single alphabet character, or "PAUSE" or "BACKSPACE").

Example

    For

wordList = ["under", "understand", "understanding", "understandable", "unacceptable", "undeniable", "unilateral", "universe", "universal", "underestimated", "understated"]

and

actions = ["u", "n", "PAUSE", "d", "e", "PAUSE", "r", "s", "t", "a", "PAUSE", "t", "e", "PAUSE"]

the output should be

autocomplete(wordList, actions) = [["unacceptable", "undeniable", "under", "underestimated", "understand", "understandable", "understanding", "understated", "unilateral", "universal", "universe"],
                                   ["undeniable", "under", "underestimated", "understand", "understandable", "understanding", "understated"],
                                   ["understand", "understandable", "understanding", "understated"],
                                   ["understated"]]

    For

wordList = ["cats", "cat", "cap", "cape", "cute", "cuts"]

and

actions = ["c", "a", "PAUSE", "BACKSPACE", "u", "t", "PAUSE"]

the output should be

autocomplete(wordList, actions) = [["cap", "cape", "cat", "cats"],
                                   ["cute", "cuts"]]

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] array.string wordList

    An array of all the words that autocomplete suggestions will be based on. There are no duplicate words within the list.

    Guaranteed constraints:

    0 ≤ wordList.length ≤ 150000,
    0 ≤ wordList[i].length ≤ 21.

    [input] array.string actions

    An array of actions the user has taken (in order), consisting of alphabet characters, backspaces, and pauses.

    Guaranteed constraints:
    0 ≤ actions.length ≤ 105,
    actions[i] ∈ {"A" - "Z", "a" - "z", "BACKSPACE", "PAUSE"}.

    [output] array.array.string

    The length of this array should be equal to the number of "PAUSE" commands in the actions array, and each element is an array of suggested words at the time of the pause.
*/

class Trie {
    // A Trie node
    struct Node {
        bool isLeaf = false;
        std::unordered_map<char, std::unique_ptr<Node>> map {};
    };
    
    // Head of the trie 
    std::unique_ptr<Node> head;
    
public:
    Trie() : head{nullptr} {}
    Trie(const std::string& str)
        : head{nullptr}
    {
        insert(head, str);
    }
    
    Trie(const Trie& other)
        : head{clone(other.head)} {}

    Trie& operator=(const Trie& other)
    {
        Trie tmp {other};
        std::swap(tmp.head, this->head);
        
        return *this;
    }
    
    template<typename Iter, 
             typename Underlying = typename std::iterator_traits<Iter>::value_type,
             typename = std::enable_if_t<std::is_convertible<Underlying,std::string>::value,void>>
    Trie(Iter first, Iter last)
        : Trie()
    {
        while (first != last) {
            this->insert(*first);
            first = std::next(first);
        }    
    }
    
    Trie(const std::initializer_list<const char*>& lst)
        : Trie(std::begin(lst), std::end(lst)) {}

    Trie(std::initializer_list<const char*>&& lst)
        : Trie(std::make_move_iterator(std::begin(lst)), 
               std::make_move_iterator(std::end(lst))) {}  

    Trie(Trie&&) = default;
    Trie& operator=(Trie&&) = default;
    ~Trie() noexcept = default;
    
    void insert(const std::string& str)
    {
        insert(head, str);
    }
    
    void erase(const std::string& str)
    {
        deletion(head, str);
    }
    
    bool search(const std::string& str) const noexcept
    {
        return search(head, str);
    }
    
    bool empty() const noexcept
    {
        return head == nullptr;
    }
    
    /* This function returns a vector of strings representing suggestions
     * of words based on the prefix input (autocompletion feature) */    
    std::vector<std::string> suggestions(std::string& prefix)
    {
        std::vector<std::string> res;
        
        // find the starting node
        auto node = head.get();
        if (!node) return res;
        
        for (std::size_t i=0; i<prefix.size(); ++i) {    
            if (!node->map[prefix[i]]) {
                return res; // return empty vector (no suggestions possible)
            }
            
            node = node->map[prefix[i]].get();
        }
        
        // traverse from there
        suggestions(prefix, res, node);
        
        // sort results
        std::sort(begin(res), end(res));
        
        return res;
    }
        
private:
    // Function that returns a new Trie node
    inline std::unique_ptr<Node> getNewTrieNode() const
    {
        return std::make_unique<Node>();
    }
    
    // Function to clone a Trie
    std::unique_ptr<Node> clone(const std::unique_ptr<Node>& node) const
    {
        if (!node) return nullptr;
        else {
            std::unique_ptr<Node> newnode {getNewTrieNode()};
            
            newnode->isLeaf = node->isLeaf;
            
            for (auto& p: node->map) {
                if (p.second) {
                    newnode->map[p.first] = clone(node->map[p.first]);
                }
            }
            
            return newnode;
        }
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
            if (!head->map[str[index]]) {
                head->map[str[index]] = getNewTrieNode();
            }
            insert(head->map[str[index]], str, index+1);
        }
    }
    
    // returns true if given node has any children
    bool haveChildren(const std::unique_ptr<Node>& curr) const
    {
        // don't use (curr->map).size() to check for children

        for (const auto& it : curr->map)
            if (it.second)
                return true;

        return false;
    }
    
    // Recursive function to delete a string in Trie.
    bool deletion(std::unique_ptr<Node>& curr, 
                  const std::string& str, 
                  std::size_t index = 0)
    {
        if (!curr) return false;
        
        // if we have not reached the end of the string
        if (index < str.size()) {
            // recurse for the node corresponding to next character in
            // the string and if it returns true, delete current node
            // (if it is non-leaf)
            if (curr->map[str[index]]) {
                if (deletion(curr->map[str[index]], str, index+1)) {
                    if (curr->isLeaf == false) {
                        if (!haveChildren(curr)) {
                            curr.reset();
                            return true;
                        }
                        else {return false;}
                    }
                }
            }
        }
        else { // we have reached end of the string
            if (curr->isLeaf) {
                // if current node is a leaf node and don't have any children
                if (!haveChildren(curr)) {
                    curr.reset();
                    return true;
                }
                else { // if current node is a leaf node and have children
                    curr->isLeaf = false; // mark current node as non-leaf node (DON'T DELETE IT)
                    return false;
                }
            }
        }
        
        return false;
    }
    
    // Recursive function to find a string in Trie. It returns true
    // if the string is found in the Trie, else it returns false
    bool search(const std::unique_ptr<Node>& head, 
                const std::string& str, 
                std::size_t index = 0) const noexcept
    {
        if (!head) return false;
        else if (index == str.size()) {return head->isLeaf;}
        else return search(head->map[str[index]], str, index+1);
    }
    
    // Recursive function implementing autocompletion feature
    void suggestions(std::string& pref, std::vector<std::string>& res, Node* node)
    {
        if (node->isLeaf) {
            res.emplace_back(pref);
        }
            
        for (auto& p: node->map) {
            if (p.second) {
                pref.push_back(p.first);
                suggestions(pref, res, p.second.get());
                pref.pop_back();
            }
        }
    }
       
}; // end of class Trie

auto autocomplete(vector<string> wordList, vector<string> actions) {
    vector<vector<string>> res;
    Trie trie (begin(wordList), end(wordList));
    string curr = "";
    
    for (auto& s: actions) {
        if (s == "PAUSE") {res.push_back(trie.suggestions(curr));}
        else if (s == "BACKSPACE") {if (curr.size() > 0) curr.pop_back();}
        else {curr += s;}
    }
    
    return res;
}
