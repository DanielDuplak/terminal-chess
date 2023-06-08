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

TEST test_is_game_over()
{
    struct piece* board[BOARD_ROWS][BOARD_COLS];

    create_board_fen(board, "r5kr/ppp2Q2/1b1p3p/1N4p1/1P6/5R1P/P1q2P2/2B2RK1");
    ASSERT(is_game_over(board, false));
    destroy_game(board);

    PASS();
}


SUITE(test_game)
{
    RUN_TEST(test_destroy_game);
    RUN_TEST(test_is_game_over);
}