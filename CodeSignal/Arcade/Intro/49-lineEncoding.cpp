/*Given a string, return its encoding defined as follows:

    First, the string is divided into the least possible number of disjoint substrings consisting of identical characters
        for example, "aabbbc" is divided into ["aa", "bbb", "c"]
    Next, each substring with length greater than one is replaced with a concatenation of its length and the repeating character
        for example, substring "bbb" is replaced by "3b"
    Finally, all the new strings are concatenated together in the same order and a new string is returned.

Example

For s = "aabbbc", the output should be
lineEncoding(s) = "2a3bc".

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] string s

    String consisting of lowercase English letters.

    Guaranteed constraints:
    4 ≤ s.length ≤ 15.

    [output] string

    Encoded version of s.
*/

std::string lineEncoding(std::string s) {
    std::string result;
    std::size_t count = 1;
    s.push_back('-'); // padding - unused
    for (std::size_t i = 1; i < s.size(); ++i) {
        if (s[i] == s[i-1]) {
            ++count;
        } 
        else {
            if (count > 1) {
                result += to_string(count);
            } 
            result += s[i-1];
            count = 1; 
        }
    }
    return result;
}
