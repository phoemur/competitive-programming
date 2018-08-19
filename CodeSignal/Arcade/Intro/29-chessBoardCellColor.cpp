/*Given two cells on the standard chess board, determine whether they have the same color or not.

Example

    For cell1 = "A1" and cell2 = "C3", the output should be
    chessBoardCellColor(cell1, cell2) = true.

    For cell1 = "A1" and cell2 = "H3", the output should be
    chessBoardCellColor(cell1, cell2) = false.

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] string cell1

    [input] string cell2

    [output] boolean

    true if both cells have the same color, false otherwise.
*/

bool chessBoardCellColor(std::string cell1, std::string cell2) {
    std::vector<int> t {0, 1, 0, 1,
                        0, 1, 0, 1};
    std::map<char, std::vector<int>> table = {
        {'A', t},
        {'C', t},
        {'E', t},
        {'G', t}};
    std::rotate(t.begin(), t.begin()+1, t.end());
    table.insert({{'B', t},
                  {'D', t},
                  {'F', t},
                  {'H', t}});
    
    return table[cell1[0]][cell1[1] - '0' - 1] ==
           table[cell2[0]][cell2[1] - '0' - 1];
}
