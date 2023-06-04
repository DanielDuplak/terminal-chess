#include "piece.h"
#include "game.h"


#define RED   "\x1B[31m"
#define YEL   "\x1B[33m"
#define RESET "\x1B[0m"

void create_board(struct piece* board[ROWS][COLS]);

void render_board(struct piece* board[ROWS][COLS]);

void render_line();

char get_piece_char_for_render(enum piece_type type);