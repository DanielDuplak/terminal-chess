#include <stdio.h>
#include "board.h"

int main()
{
    struct piece* board[ROWS][COLS];
    create_board(board);
    render_board(board);

    for(int row = 0; row < ROWS; row++)
    {
        for(int col = 0; col < COLS; col++)
        {
            destroy_piece(board[row][col]);
        }
    }
    return 0;
}