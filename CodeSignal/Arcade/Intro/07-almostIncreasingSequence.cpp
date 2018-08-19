/*Given a sequence of integers as an array, determine whether it is possible to obtain a strictly increasing sequence by removing no more than one element from the array.

Example

    For sequence = [1, 3, 2, 1], the output should be
    almostIncreasingSequence(sequence) = false.

    There is no one element in this array that can be removed in order to get a strictly increasing sequence.

    For sequence = [1, 3, 2], the output should be
    almostIncreasingSequence(sequence) = true.

    You can remove 3 from the array to get the strictly increasing sequence [1, 2]. Alternately, you can remove 2 to get the strictly increasing sequence [1, 3].

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] array.integer sequence

    Guaranteed constraints:
    2 ≤ sequence.length ≤ 105,
    -105 ≤ sequence[i] ≤ 105.

    [output] boolean

    Return true if it is possible to remove one element from the array in order to get a strictly increasing sequence, otherwise return false.
*/

bool is_unique(vector<int>& x) {
    sort( x.begin(), x.end() ); // O(N log N)
    return adjacent_find( x.begin(), x.end() ) == x.end();
}

bool is_sorted_skip(vector<int> buffer, int skip)
{
    buffer.erase(buffer.begin()+skip);
    return std::is_sorted(buffer.begin(), buffer.end()) &&
           is_unique(buffer);
}

bool almostIncreasingSequence(std::vector<int>& v) {
    auto iter = std::adjacent_find(v.begin(),
                                   v.end(),
                                   [](int L, int R){ return L >= R; });
    if (is_sorted_skip(v, std::distance(v.begin(), iter))) {
        return true;
    }
    return is_sorted_skip(v, std::distance(v.begin(), iter+1));
}
