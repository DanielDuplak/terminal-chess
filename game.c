#include "game.h"
#include <stdio.h>
#include <stdlib.h>

bool is_game_over(struct piece* board[ROWS][COLS], bool is_whites_turn)
{ 
    for(int row = 0; row < ROWS; row++)
    {
        for(int col = 0; col < COLS; col++)
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
    struct piece* board[ROWS][COLS];
    create_board(board);
    bool is_whites_turn = true;
    
    while(!is_game_over(board, is_whites_turn))
    {
        system("clear");
        render_board(board);
        int select_row = -1;
        int select_col = -1;
        int input_row = -2;
        int input_col = -2;
        printf("is whites turn: %d\n", is_whites_turn);
        do
        {
            printf("select piece\n");
            scanf("%d %d", &select_row, &select_col);
        }while(!update_potential_moves(board, is_whites_turn, select_row, select_col));
        
        render_potential_moves(board[select_row][select_col]);
        do
        {
            printf("Select input: select row: %d, select col: %d\n", select_row, select_col);
            scanf("%d %d", &input_row, &input_col);
            printf("%d %d\n", input_row, input_col);
            
            //if(input_row == -1 && input_col == -1)
            //{
            //    continue;
            //}
            
        }while(!move_piece(board, select_row, select_col, input_row, input_col));
        is_whites_turn = !is_whites_turn;
    }

    destroy_game(board);
}

void render_potential_moves(struct piece* piece)
{
    if(piece == NULL)
    {
        return;
    }
    printf("Potential moves:\n");
    struct move* current = piece->move_list;
    while(current != NULL)
    {
        printf("%d %d\n", current->row, current->col);
        current = current->next;
    }
}

void destroy_game(struct piece* board[ROWS][COLS])
{
    for(int row = 0; row < ROWS; row++)
    {
        for(int col = 0; col < COLS; col++)
        {
            destroy_piece(board[row][col]);
        }
    }
}