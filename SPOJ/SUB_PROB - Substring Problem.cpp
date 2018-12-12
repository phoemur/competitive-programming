/*SUB_PROB - Substring Problem
no tags 

String Matching is an important problem in computer science research and finds applications in Bioinformatics, Data mining,pattern recognition, Internet security and many more areas.

The problem we consider here is a smaller version of it. You are given a string M and N other strings smaller in length than M. You have to find whether each of these N strings is a substring of M. All strings consist of only alphanumeric characters.

You are required to write a C/CPP code to solve the problem.
Input

Input to the program consists of a series of lines. The first line contains the string M (no more than 100000 characters long). The next line contains an integer N (<1000) the number of query strings. Each of the next N lines contain a string S (each of which is no more than 2000 characters long).
Output

Output should consist of N lines each with a character 'Y'/'N' indicating whether the string S is a substring of String M or not.
Example

Input:

abghABCDE
2
abAB
ab




Output:
 

N
Y


Note: The test data for this problem not only consist of the official test cases from the contest,as well some cases of my own.

A testcase is added on 25.7.2010, after rejudging 3 users loose accepted.*/

#include <queue>
#include <unordered_map>
#include <vector>
#include <iostream>

// Reference https://www.toptal.com/algorithms/aho-corasick-algorithm
class Aho {
    
    // A vertex from the trie
    struct Vertex {
        std::unordered_map<char, int> children {}; // Links to the child vertexes in the trie
        bool leaf = false;      // Flag that some word from the dictionary ends in this vertex
        char parent_char;       // Char which moves us from the parent vertex to the current vertex
        int        parent = -1; // Link to the parent vertex
        int   suffix_link = -1; // Suffix link from current vertex (the equivalent of P[i] from the KMP algorithm)
        int end_word_link = -1; // Link to the leaf vertex of the maximum-length word we can make from the current prefix
        int       word_ID = -1; // If the vertex is the leaf, we store the ID of the word
    };

    std::vector<Vertex> trie;
    std::vector<int> words_length;
    int size;
    int root;
    int wordID; // id of the last inserted word
    
public:
    
    Aho()
        : trie{}, words_length{}, size{0}, root{0}, wordID{0}
    {
        // Add root node
        trie.push_back(Vertex{});
        ++size;
    }
    
    void add_string(const std::string& s)
    {
        int curVertex = root;
        
        
        for (char c : s) // Iterating over the string's characters
        {
            // Checking if a vertex with this edge exists in the trie:
            if (trie[curVertex].children.find(c) == trie[curVertex].children.end())
            {
                trie.push_back(Vertex{});

                trie[size].parent = curVertex;
                trie[size].parent_char = c;
                trie[curVertex].children[c] = size;
                size++;
            }
            
            curVertex = trie[curVertex].children[c]; // Move to the new vertex in the trie
        }

        // Mark the end of the word and store its ID
        trie[curVertex].leaf = true;
        trie[curVertex].word_ID = wordID;
        words_length.push_back(s.size());
        
        ++wordID;
    }
    
    void prepare()
    {
        std::queue<int> vertexQueue {};
        vertexQueue.push(root);
	
        while (!vertexQueue.empty())
        {
            int curVertex = vertexQueue.front();
            vertexQueue.pop();
            
            CalcSuffLink(curVertex);

            for (const auto& p : trie[curVertex].children)
            {
                vertexQueue.push(trie[curVertex].children[p.first]);
            }
        }
    }
    
    void process(const std::string& text, std::vector<bool>& result)
    {
        // Current state value
        int currentState = root;

        for (int j = 0; j < text.size(); j++)
        {
            // Calculating new state in the trie
            while (true)
            {
                // If we have the edge, then use it
                if (trie[currentState].children.find(text[j]) != trie[currentState].children.end())
                {
                    currentState = trie[currentState].children[text[j]];
                    break;
                }
                
                // Otherwise, jump by suffix links and try to find the edge with
                // this char

                // If there aren't any possible edges we will eventually ascend to
                // the root, and at this point we stop checking.
                if (currentState == root) break;
                
                currentState = trie[currentState].suffix_link;
            }

            int checkState = currentState;

            // Trying to find all possible words from this prefix
            while (true)
            { 
                // Checking all words that we can get from the current prefix
                checkState = trie[checkState].end_word_link;

                // If we are in the root vertex, there are no more matches
                if (checkState == root) break;			

                // Store result
                result[trie[checkState].word_ID] = true; // Found this word
                
                // Trying to find all matched patterns of smaller length
                checkState = trie[checkState].suffix_link;
            }
        }
    }
    
private:
    
    void CalcSuffLink(int vertex)
    {
        // Processing root (empty string)
        if (vertex == root)
        { 
            trie[vertex].suffix_link = root;
            trie[vertex].end_word_link = root;
            return;
        }

        // Processing children of the root (one character substrings)
        if (trie[vertex].parent == root)
        { 
            trie[vertex].suffix_link = root;
            
            if (trie[vertex].leaf) trie[vertex].end_word_link = vertex;
            else trie[vertex].end_word_link = trie[trie[vertex].suffix_link].end_word_link;
            
            return;
        }

        // Cases above are degenerate cases as for prefix function calculation; the
        // value is always 0 and links to the root vertex.

        // To calculate the suffix link for the current vertex, we need the suffix
        // link for the parent of the vertex and the character that moved us to the
        // current vertex.

        int curBetterVertex = trie[trie[vertex].parent].suffix_link;
        char chVertex = trie[vertex].parent_char; 

        // From this vertex and its substring we will start to look for the maximum
        // prefix for the current vertex and its substring.

        while (true)
        {
            // If there is an edge with the needed char, we update our suffix link
            // and leave the cycle
            if (trie[curBetterVertex].children.find(chVertex) != trie[curBetterVertex].children.end())
            {
                trie[vertex].suffix_link = trie[curBetterVertex].children[chVertex];
                break;
            }
            
            // Otherwise, we are jumping by suffix links until we reach the root
            // (equivalent of k == 0 in prefix function calculation) or we find a
            // better prefix for the current substring.
            if (curBetterVertex == root)
            { 
                trie[vertex].suffix_link = root;
                break;
            }
            
            curBetterVertex = trie[curBetterVertex].suffix_link; // Go back by sufflink
        }
        
        // When we complete the calculation of the suffix link for the current
        // vertex, we should update the link to the end of the maximum length word
        // that can be produced from the current substring.
        if (trie[vertex].leaf) trie[vertex].end_word_link = vertex; 
        else trie[vertex].end_word_link = trie[trie[vertex].suffix_link].end_word_link;
}

}; // end of class Aho

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string text;
    std::cin >> text;
    
    int n;
    std::cin >> n;
    
    Aho ahotrie {};
    
    std::vector<bool> found (n, false); // Check if this string was found
    std::vector<std::string> input; // Store input
    std::unordered_map<std::string, int> ids; // Map input to string ID on trie
    int cur = 0;
    
    while (n--)
    {
        std::string i;
        std::cin >> i;
        
        input.emplace_back(i);
        ids[i] = cur++;
        
        ahotrie.add_string(i);
    }
    
    ahotrie.prepare();
    ahotrie.process(text, found);
    
    for (auto& s : input)
    {
        if (found[ids[s]])
            std::cout << "Y\n";
        else
            std::cout << "N\n";
    }
    
    return 0;
}

