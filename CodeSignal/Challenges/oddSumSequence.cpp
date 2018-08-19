/*Given an array of integers, we can produce a new array by replacing each element with the sum of all the odd integers up to that index. For example, the array [2, 5, 3, 8, 1] would produce the result [0, 5, 8, 8, 9].

If we keep repeating this process, we'll get a sequence of arrays that'll eventually start repeating, but it may need to go through a few iterations before the repetition begins. Given the array arr, determine how many steps it'll take for the sequence to reach a point where it'll start repeating.

Example

    For arr = [2, 5, 3, 8, 1], the output should be oddSumSequence(arr) = 3

    The sequence of arrays would look like this:

    [2, 5, 3, 8, 1]
    [0, 5, 8, 8, 9]
    [0, 5, 5, 5, 14]
    [0, 5, 10, 15, 15]
    [0, 5, 5, 20, 35]
    [0, 5, 10, 10, 45]
    [0, 5, 5, 5, 50]
    [0, 5, 10, 15, 15]
             .
             .
             .

    At this point the sequence has reached an array we've already seen before, so it'll continue to repeat. Since it took 3 steps to reach the array [0, 5, 10, 15, 15] the first time, the answer is 3.

    For arr = [0], the output should be oddSumSequence(arr) = 0

    Every array in the sequence would be [0], which is the same as the original array, so it didn't take any steps for it to start repeating. So the answer is 0.

Input / Output

    [execution time limit] 0.5 seconds (cpp)

    [input] array.integer arr

    An array of non-negative integers.

    Guaranteed constraints:
    1 ≤ arr.length ≤ 20
    0 ≤ arr[i] ≤ 106

    [output] integer

    An integer representing how many steps it'll take before the sequence of arrays starts repeating.
*/

int oddSumSequence(auto a) {
    map<decltype(a),int> T;

    for (int i=1;; ++i) {
        T[a] = i;
        
        int x = 0;
        for (auto& n: a) {
            if (n & 1) x += n;
            n = x;
        } 
        
        if (T[a]) return T[a]-1;
    }
}
