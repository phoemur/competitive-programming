/*Sudoku is a number-placement puzzle. The objective is to fill a 9 × 9 grid with digits so that each column, each row, and each of the nine 3 × 3 sub-grids that compose the grid contains all of the digits from 1 to 9.

This algorithm should check if the given grid of numbers represents a correct solution to Sudoku.

Example

For the first example below, the output should be true. For the other grid, the output should be false: each of the nine 3 × 3 sub-grids should contain all of the digits from 1 to 9.

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] array.array.integer grid

    A matrix representing 9 × 9 grid already filled with numbers from 1 to 9.

    [output] boolean

    true if the given grid represents a correct solution to Sudoku, false otherwise.
*/

bool sudoku(std::vector<std::vector<int>> grid) {
    // check squares
    std::set<int> square;
    for (int i = 0; i <grid.size(); i+= 3) {
        for (int j= 0; j< grid.size(); j+=3) {
            square.clear();
            for (int n=0; n< 3; ++n) {
                for (int m=0; m<3; ++m) {
                    square.insert(grid[i+n][j+m]);
                }
            }
            if (square.size() != 9) {return false;}
        }
    }
    
    // check columns and lines
    for (int test = 0; test < grid.size(); ++test) {
        for (int i=0; i< grid.size(); ++i) {
            for (int j=0; j<grid.size(); ++j) {
                if (grid[i][test] == grid[j][test] && i != j) { // columns
                    return false;
                }
                else if (grid[test][i] == grid[test][j] && i != j){// lines
                    return false;
                }
            }
        }
    }    
    return true;
}
