#include "greatest.h"
#include "../game.h"

TEST test_destroy_game()
{
    struct piece* board[BOARD_ROWS][BOARD_COLS];
    create_board_fen(board, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    destroy_game(board);

    for(int row = 0; row < BOARD_ROWS; row++)
    {
        for(int col = 0; col < BOARD_COLS; col++)
        {
            ASSERT(board[row][col] == NULL);
        }
    }
    PASS();
}


SUITE(test_game)
{
    RUN_TEST(test_destroy_game);
}