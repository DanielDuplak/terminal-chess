#include "piece.h"

#define ROWS 8
#define COLS 8

#define RED   "\x1B[31m"
#define YEL   "\x1B[33m"
#define RESET "\x1B[0m"

void create_board(struct piece* board[ROWS][COLS]);

void render_board(struct piece* board[ROWS][COLS]);

void render_line();

void print_letters();

char get_piece_char_for_render(enum piece_type type);