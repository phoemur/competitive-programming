/*Given a string, find out if its characters can be rearranged to form a palindrome.

Example

For inputString = "aabb", the output should be
palindromeRearranging(inputString) = true.

We can rearrange "aabb" to make "abba", which is a palindrome.

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] string inputString

    A string consisting of lowercase English letters.

    Guaranteed constraints:
    1 ≤ inputString.length ≤ 50.

    [output] boolean

    true if the characters of the inputString can be rearranged to form a palindrome, false otherwise.
*/

bool palindromeRearranging(std::string inputString) {
    std::unordered_map<char, int> dic;
    
    for(char c: inputString) dic[c]++;
    
    bool one_even = false;
    for(auto& p: dic){
        if (p.second % 2 != 0){
            if (one_even){
                return false;
            } else {
                one_even = true;
            }
        }
    }
    return true;
}
