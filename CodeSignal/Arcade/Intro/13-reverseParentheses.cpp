/*You have a string s that consists of English letters, punctuation marks, whitespace characters, and brackets. It is guaranteed that the parentheses in s form a regular bracket sequence.

Your task is to reverse the strings contained in each pair of matching parentheses, starting from the innermost pair. The results string should not contain any parentheses.

Example

For string s = "a(bc)de", the output should be
reverseParentheses(s) = "acbde".

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] string s

    A string consisting of English letters, punctuation marks, whitespace characters and brackets. It is guaranteed that parentheses form a regular bracket sequence.

    Constraints:
    5 ≤ s.length ≤ 55.

    [output] string
*/

auto reverseParentheses(std::string s) 
{
    while (s.find_first_of("()") != std::string::npos) {
        auto lhs = s.find_last_of("(");
        auto rhs = s.find(")", lhs);
        std::reverse(s.begin()+lhs, s.begin()+rhs);
        s.erase(s.begin()+s.find_last_of("("));
        s.erase(s.begin()+s.find(")", lhs));
    }
    return s;
}
