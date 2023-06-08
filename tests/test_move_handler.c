#include "greatest.h"
#include "../game.h"



TEST test_get_pawn_moves() 
{
    struct piece* board[BOARD_ROWS][BOARD_COLS];

    create_board_fen(board, "8/p7/8/8/8/8/P7/8");
    bool result1 = get_pawn_moves(board, true, 6, 0);
    bool result2 = get_pawn_moves(board, true, 1, 0);
    ASSERT(result1 == true);
    ASSERT(result2 == true);

    struct move* current = board[6][0]->move_list;
    ASSERT(current != NULL);
    while(current != NULL)
    {
        ASSERT(current->row == 4 || current->row == 5);
        ASSERT(current->col == 0);
        current = current->next;
    }
    destroy_game(board);
    PASS();
}

TEST test_is_piece_in_check()
{
    struct piece* board1[BOARD_ROWS][BOARD_COLS];
    create_board_fen(board1, "5k2/8/8/8/1B6/8/8/8");
    ASSERT(is_piece_in_check(board1, 0, 5));
    destroy_game(board1);

    struct piece* board2[BOARD_ROWS][BOARD_COLS];
    create_board_fen(board2, "8/8/4k3/8/5N2/8/8/8");
    ASSERT(is_piece_in_check(board2, 2, 4));
    destroy_game(board2);

    struct piece* board3[BOARD_ROWS][BOARD_COLS];
    create_board_fen(board3, "8/8/5r2/8/8/8/5P2/8");
    ASSERT(is_piece_in_check(board3, 6, 5));
    destroy_game(board3);

    struct piece* board4[BOARD_ROWS][BOARD_COLS];
    create_board_fen(board4, "8/1r3p2/8/7b/8/8/3K4/8");
    ASSERT(is_piece_in_check(board4, 6, 3) == false);
    destroy_game(board4);

    PASS();
}

TEST test_is_king_in_check()
{
    struct piece* board[BOARD_ROWS][BOARD_COLS];

    create_board_fen(board, "5b2/8/4n3/q7/8/5p2/8/2K5");
    ASSERT(is_king_in_check(board, true) == false);
    destroy_game(board);


    create_board_fen(board, "5b2/8/4n3/q7/8/5p2/8/2K5");
    ASSERT(is_king_in_check(board, false) == false);
    destroy_game(board);


    create_board_fen(board, "8/2k5/8/8/8/4N1B1/8/1Q6");
    ASSERT(is_king_in_check(board, false));
    destroy_game(board);
    
    create_board_fen(board, "8/2k5/8/3N4/8/8/5B2/1Q6");
    ASSERT(is_king_in_check(board, false));
    destroy_game(board);

    create_board_fen(board, "8/1r6/5b2/8/8/q1p5/3K4/8");
    ASSERT(is_king_in_check(board, true));
    destroy_game(board);

    create_board_fen(board, "rnbqkbnr/ppppp1pp/5p2/7Q/4P3/8/PPPP1PPP/RNB1KBNR");
    ASSERT(is_king_in_check(board, false));
    destroy_game(board);

    PASS();
}


SUITE (test_move_handler) 
{
    RUN_TEST(test_get_pawn_moves);
    RUN_TEST(test_is_piece_in_check);
    RUN_TEST(test_is_king_in_check);
}

