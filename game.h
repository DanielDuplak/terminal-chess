#include "move_handler.h"

bool is_game_over(struct piece* board[ROWS][COLS], bool is_whites_turn);

void play_game();

void destroy_game(struct piece* board[ROWS][COLS]);

void render_potential_moves(struct piece* piece);