#include "piece.h"

#define BOARD_ROWS 8
#define BOARD_COLS 8

#define RED   "\x1B[31m"
#define YEL   "\x1B[33m"
#define RESET "\x1B[0m"

void create_board(struct piece* board[BOARD_ROWS][BOARD_COLS]);

void render_board(struct piece* board[BOARD_ROWS][BOARD_COLS]);

void render_line();

void print_letters();

char get_piece_char_for_render(enum piece_type type);

void draw_board(struct piece* board[BOARD_ROWS][BOARD_COLS]);

void highlight_squares(struct piece* board[BOARD_ROWS][BOARD_COLS], int row, int col);