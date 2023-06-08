#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include "renderer.h"

bool is_game_over(struct piece* board[BOARD_ROWS][BOARD_COLS], bool is_whites_turn)
{ 
    if(is_king_in_check(board, is_whites_turn) == false)
    {
        return false;
    }
    for(int row = 0; row < BOARD_ROWS; row++)
    {
        for(int col = 0; col < BOARD_COLS; col++)
        {
            if(board[row][col] != NULL && board[row][col]->is_white == is_whites_turn)
            {
                if(update_potential_moves(board, is_whites_turn, row, col))
                {
                    return false;
                }
            }
        }
    }
    return true;
}

void play_game()
{
    struct piece* board[BOARD_ROWS][BOARD_COLS];
    //create_board(board);
    char* starting_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    create_board_fen(board, starting_fen);
    bool is_whites_turn = true;

    init_rendering();
    int a = 0;
    
    while(!is_game_over(board, is_whites_turn))
    {
        draw_board(board);
        refresh();
        int mx, my;
        int row, col = -1;
        int row_move, col_move = -1;

        do
        {
            handle_mouse_events(&my, &mx);
            convert_mouse_pos_to_board_pos(my, mx, &row, &col);
        } while (!update_potential_moves(board, is_whites_turn, row, col));

        highlight_squares(board, row, col);
        refresh();
        handle_mouse_events(&my, &mx);
        convert_mouse_pos_to_board_pos(my, mx, &row_move, &col_move);

        if(!move_piece(board, row, col, row_move, col_move))
        {
            continue;
        }
        is_whites_turn = !is_whites_turn;
        
    }

    refresh();
    destroy_game(board);
    endwin();
    exit(0);
}

void convert_mouse_pos_to_board_pos(int y, int x, int* row, int* col)
{
    *row = y/2;
    *col = x/4;
}

void handle_mouse_events(int* y, int* x)
{
    MEVENT event;
    int c;
    int exit_flag = 0;

    while (!exit_flag) 
    {
        refresh();
        c = wgetch(stdscr);
        switch (c) 
        {
            case KEY_MOUSE:
                if (getmouse(&event) == OK) 
                {
                    if(event.bstate & (BUTTON1_CLICKED))
                    {	
                        *x = event.x;
                        *y = event.y;
                        exit_flag = 1;
                    }
                }
                break;
        }
    }
}

void destroy_game(struct piece* board[BOARD_ROWS][BOARD_COLS])
{
    for(int row = 0; row < BOARD_ROWS; row++)
    {
        for(int col = 0; col < BOARD_COLS; col++)
        {
            board[row][col] = destroy_piece(board[row][col]);
        }
    }
}