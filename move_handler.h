#include "board.h"
#include <stdbool.h>


bool update_potential_moves(struct piece* board[BOARD_ROWS][BOARD_COLS],  bool whites_turn, int row, int col);

void add_move_to_piece(struct piece* piece, int row, int col);

bool get_pawn_moves(struct piece* board[BOARD_ROWS][BOARD_COLS], bool whites_turn, int row, int col);

bool get_straight_moves(struct piece* board[BOARD_ROWS][BOARD_COLS], int row, int col);

bool get_diagonal_moves(struct piece* board[BOARD_ROWS][BOARD_COLS], int row, int col);

bool get_knight_moves(struct piece* board[BOARD_ROWS][BOARD_COLS], int row, int col);

bool get_king_moves(struct piece* board[BOARD_ROWS][BOARD_COLS], int row, int col);

bool is_piece_in_check(struct piece* board[BOARD_ROWS][BOARD_COLS], int row, int col);

bool is_king_in_check(struct piece* board[BOARD_ROWS][BOARD_COLS], bool whites_turn);

bool try_potential_moves(struct piece* board[BOARD_ROWS][BOARD_COLS], bool whites_turn, int row, int col);

bool move_piece(struct piece* board[BOARD_ROWS][BOARD_COLS], int cur_row, int cur_col, int row, int col);
