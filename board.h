#include "piece.h"

#define BOARD_ROWS 8
#define BOARD_COLS 8

#define RED   "\x1B[31m"
#define YEL   "\x1B[33m"
#define RESET "\x1B[0m"

void create_board(struct piece* board[BOARD_ROWS][BOARD_COLS]);

void create_board_fen(struct piece* board[BOARD_ROWS][BOARD_COLS], const char* fen_string);

char get_piece_char_for_render(enum piece_type type);

void draw_board(struct piece* board[BOARD_ROWS][BOARD_COLS]);

void highlight_squares(struct piece* board[BOARD_ROWS][BOARD_COLS], int row, int col);