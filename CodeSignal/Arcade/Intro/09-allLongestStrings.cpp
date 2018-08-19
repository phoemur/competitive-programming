/*Given an array of strings, return another array containing all of its longest strings.

Example

For inputArray = ["aba", "aa", "ad", "vcd", "aba"], the output should be
allLongestStrings(inputArray) = ["aba", "vcd", "aba"].

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] array.string inputArray

    A non-empty array.

    Guaranteed constraints:
    1 ≤ inputArray.length ≤ 10,
    1 ≤ inputArray[i].length ≤ 10.

    [output] array.string

    Array of the longest strings, stored in the same order as in the inputArray.
*/

auto get_longest(const std::vector<std::string>& v)
{
    std::size_t max = 0;
    std::for_each(v.begin(), v.end(), [&max](auto& str){
        if (str.length() > max) {
            max = str.length();
        }
    });
    return max;
}    

auto allLongestStrings(std::vector<std::string> v) 
{
    auto size = get_longest(v);
    v.erase(std::remove_if(v.begin(),
                           v.end(),
                           [&size](auto& s){return s.length()<size;}),
                           v.end());
    return v;
}
