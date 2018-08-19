/*Define a word as a sequence of consecutive English letters. Find the longest word from the given string.

Example

For text = "Ready, steady, go!", the output should be
longestWord(text) = "steady".

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] string text

    Guaranteed constraints:
    4 ≤ text.length ≤ 50.

    [output] string

    The longest word from text. It's guaranteed that there is a unique output.
*/

std::string longestWord(std::string t) {
    std::for_each(t.begin(), t.end(), [](char& c){
        if (std::ispunct(c)) { c = ' ';} // swap punct for spaces
    });

    std::istringstream iss(t);
    std::vector<std::string> r ((std::istream_iterator<std::string>(iss)),
                                 std::istream_iterator<std::string>());
    
    return *std::max_element(r.begin(), r.end(),
                             [](auto &l, auto& r){
                                 return l.size() < r.size();
                             });
}
