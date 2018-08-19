/*Some people are standing in a row in a park. There are trees between them which cannot be moved. Your task is to rearrange the people by their heights in a non-descending order without moving the trees. People can be very tall!

Example

For a = [-1, 150, 190, 170, -1, -1, 160, 180], the output should be
sortByHeight(a) = [-1, 150, 160, 170, -1, -1, 180, 190].

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] array.integer a

    If a[i] = -1, then the ith position is occupied by a tree. Otherwise a[i] is the height of a person standing in the ith position.

    Guaranteed constraints:
    1 ≤ a.length ≤ 1000,
    -1 ≤ a[i] ≤ 1000.

    [output] array.integer

    Sorted array a with all the trees untouched.
*/

auto sortByHeight(std::vector<int> v) 
{
    vector<int> indexes;
    for (auto i = v.begin(); i != v.end(); ++i) {
        if (*i == -1) {
            indexes.push_back(std::distance(v.begin(), i));
        }
    }
    v.erase(remove(begin(v), end(v), -1), end(v));
    std::sort(v.begin(), v.end());
    for (auto& i: indexes) {
        v.insert(v.begin()+i, -1);
    }
    return v;
}
