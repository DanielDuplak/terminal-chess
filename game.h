#include "move_handler.h"
#include <ncurses.h>

bool is_game_over(struct piece* board[BOARD_ROWS][BOARD_COLS], bool is_whites_turn);

void play_game();

void destroy_game(struct piece* board[BOARD_ROWS][BOARD_COLS]);

void handle_mouse_events(int* y, int* x);

void convert_mouse_pos_to_board_pos(int y, int x, int* row, int* col);