/*Given a rectangular matrix containing only digits, calculate the number of different 2 × 2 squares in it.

Example

For

matrix = [[1, 2, 1],
          [2, 2, 2],
          [2, 2, 2],
          [1, 2, 3],
          [2, 2, 1]]

the output should be
differentSquares(matrix) = 6.

Here are all 6 different 2 × 2 squares:

    1 2
    2 2
    2 1
    2 2
    2 2
    2 2
    2 2
    1 2
    2 2
    2 3
    2 3
    2 1

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] array.array.integer matrix

    Guaranteed constraints:
    1 ≤ matrix.length ≤ 100,
    1 ≤ matrix[i].length ≤ 100,
    0 ≤ matrix[i][j] ≤ 9.

    [output] integer

    The number of different 2 × 2 squares in matrix.
*/

int differentSquares(std::vector<std::vector<int>> matrix) {
    std::set<std::vector<int>> result;
    for (std::size_t i = 1; i<matrix.size(); ++i) {
        for (std::size_t j = 1; j<matrix[0].size(); ++j) {
            result.insert({matrix[i-1][j-1],
                           matrix[i-1][ j ],
                           matrix[ i ][j-1],
                           matrix[ i ][ j ]});
        }
    }
    
    return result.size();
}
