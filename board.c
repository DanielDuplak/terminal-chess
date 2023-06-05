#include "board.h"
#include <stdio.h>


void create_board(struct piece* board[ROWS][COLS])
{
    for(int row = 0; row < ROWS; row++)
    {
        for(int col = 0; col < COLS; col++)
        {
            board[row][col] = NULL;
        }
    }

    for(int i = 0; i < COLS; i++)
    {
        board[6][i] = create_piece(PAWN, true);
        board[1][i] = create_piece(PAWN, false);
        if(i == 0 || i == 7)
        {
            board[7][i] = create_piece(ROOK, true);
            board[0][i] = create_piece(ROOK, false);
        }
        else if(i == 1 || i == 6)
        {
            board[7][i] = create_piece(KNIGHT, true);
            board[0][i] = create_piece(KNIGHT, false);
        }
        else if(i == 2 || i == 5)
        {
            board[7][i] = create_piece(BISHOP, true);
            board[0][i] = create_piece(BISHOP, false);
        }
        else if(i == 3)
        {
            board[7][i] = create_piece(QUEEN, true);
            board[0][i] = create_piece(QUEEN, false);

            board[7][i+1] = create_piece(KING, true);
            board[0][i+1] = create_piece(KING, false);
        }
    }
}


void render_board(struct piece* board[ROWS][COLS])
{
    char c;
    print_letters();
    render_line();
    for(int row = 0; row < ROWS; row++)
    {
        printf("%d ", 8-row);
        for(int col = 0; col < COLS; col++)
        {
            printf(YEL "| " RESET);
            if(board[row][col] != NULL)
            {
                c = (board[row][col] == NULL) ? ' ' : get_piece_char_for_render(board[row][col]->type);
                printf((board[row][col]->is_white) ? "%c " : RED "%c " RESET, c);
            }
            else
            {
                printf("  ");
            }

            if(col == COLS-1)
            {
                printf(YEL "|\n" RESET);
            }
        }
        render_line();
    }
}

void render_line()
{
    printf("  ");
    for(int i = 0; i < ROWS; i++)
    {
        printf(YEL "o---" RESET);
        if(i == 7)
        {
            printf(YEL "o\n" RESET);
        }
    }
}

void print_letters()
{
    printf("  ");
    for(int i = 0; i < ROWS; i++)
    {
        printf("  %c ", (char)(i+'A'));
    }
    printf("\n");
}

char get_piece_char_for_render(enum piece_type type)
{
    switch (type)
    {
    case PAWN:
        return 'i';
        break;
    case KNIGHT:
        return 'h';
        break;
    case BISHOP:
        return '^';
        break;
    case ROOK:
        return 'X';
        break;
    case QUEEN:
        return 'Q';
        break;
    case KING:
        return 'K';
        break;
    default:
        return 'o';
        break;
    }
}