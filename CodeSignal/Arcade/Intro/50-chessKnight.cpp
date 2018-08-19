/*Given a position of a knight on the standard chessboard, find the number of different moves the knight can perform.

The knight can move to a square that is two squares horizontally and one square vertically, or two squares vertically and one square horizontally away from it. The complete move therefore looks like the letter L. Check out the image below to see all valid moves for a knight piece that is placed on one of the central squares.

Example

    For cell = "a1", the output should be
    chessKnight(cell) = 2.

    For cell = "c2", the output should be
    chessKnight(cell) = 6.

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] string cell

    String consisting of 2 letters - coordinates of the knight on an 8 × 8 chessboard in chess notation.

    [output] integer
*/

int chessKnight(std::string cell) {
    std::size_t moves = 8;
    
    // horizontal
    switch (cell[0]) {
        case 'a': case 'h':
            moves /= 2;
            break;
        case 'b': case 'g':
            moves -= 2;
            break;
    }
    
    // vertical
    switch (cell[1]) {
        case '1': case '8':
            moves /= 2;
            break;
        case '2': case '7':
            moves -= 2;
            break;
    }
    return moves;
}
