/*Given a string, find the shortest possible string which can be achieved by adding characters to the end of initial string to make it a palindrome.

Example

For st = "abcdc", the output should be
buildPalindrome(st) = "abcdcba".

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] string st

    A string consisting of lowercase English letters.

    Guaranteed constraints:
    3 ≤ st.length ≤ 10.

    [output] string
*/

bool checkPalindrome(const std::string& x) {
    return std::equal(x.begin(), 
                      x.begin() + x.size() / 2, 
                      x.rbegin());
}

std::string buildPalindrome(const std::string& st) {
    for (std::size_t i=0; i < st.size(); ++i) {
        std::string tmp {st};
        tmp.append(std::accumulate(st.rend()-i, 
                                   st.rend(), 
                                   std::string("")));        
        if (checkPalindrome(tmp)) {return tmp;}
    }
}
