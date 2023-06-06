#include "board.h"
#include <stdio.h>
#include <ncurses.h>

void highlight_square(int row, int col);

void create_board(struct piece* board[BOARD_ROWS][BOARD_COLS])
{
    for(int row = 0; row < BOARD_ROWS; row++)
    {
        for(int col = 0; col < BOARD_COLS; col++)
        {
            board[row][col] = NULL;
        }
    }

    for(int i = 0; i < BOARD_COLS; i++)
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


void render_board(struct piece* board[BOARD_ROWS][BOARD_COLS])
{
    char c;
    print_letters();
    render_line();
    for(int row = 0; row < BOARD_ROWS; row++)
    {
        printf("%d ", 8-row);
        for(int col = 0; col < BOARD_COLS; col++)
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

            if(col == BOARD_COLS-1)
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
    for(int i = 0; i < BOARD_ROWS; i++)
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
    for(int i = 0; i < BOARD_ROWS; i++)
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

void draw_board(struct piece* board[BOARD_ROWS][BOARD_COLS]) 
{
    attron(COLOR_PAIR(8));
    for (int row = 0; row < BOARD_ROWS; row++) 
    {
        for (int col = 0; col < BOARD_COLS; col++) 
        {
            int x = col * 4;
            int y = row * 2;

            mvprintw(y, x, "o---o");
            mvprintw(y+1,x,"|");

            if (board[row][col] != NULL) 
            {
                attroff(COLOR_PAIR(8));
                if(board[row][col]->is_white)
                {
                    attron(COLOR_PAIR(6));
                }
                else
                {
                    attron(COLOR_PAIR(2));
                }
                mvprintw(y + 1, x + 2, "%c", get_piece_char_for_render(board[row][col]->type));
                attroff(COLOR_PAIR(6));
                attroff(COLOR_PAIR(2));
                attron(COLOR_PAIR(8));
            } 
            else 
            {
                mvprintw(y + 1, x + 2, "   ");
            }

            mvprintw(y+1,x+4,"|");
            if(col == 7)
            {
                mvprintw(y+2,x,"o---o");
            }
            else
            {
                mvprintw(y+2,x,"o---");
            }
        }
    }
    attroff(COLOR_PAIR(8));

    attron(COLOR_PAIR(1));
    int x = 0;
    int y = 0;
    for (int i = 0; i < BOARD_ROWS; i++) 
    {
        mvprintw(BOARD_ROWS * 2 + 1, x + 2, "%c", (char)(i+'A'));
        mvprintw(y + 1, BOARD_COLS * 4 + 2, "%d", BOARD_ROWS - i);
        y += 2;
        x += 4;
    }
    attroff(COLOR_PAIR(1));
}

void highlight_squares(struct piece* board[BOARD_ROWS][BOARD_COLS], int row, int col) 
{
    struct piece* piece = board[row][col];
    if(piece->move_list == NULL)
    {
        return;
    }
    attron(COLOR_PAIR(1));
    struct move* current = piece->move_list;
    while(current != NULL)
    {
        highlight_square(current->row, current->col);
        current = current->next;
    }
    highlight_square(row, col);

    attroff(COLOR_PAIR(1));
}

void highlight_square(int row, int col)
{
    int x = col * 4;
    int y = row * 2;
    mvprintw(y, x, "o---o");
    mvprintw(y+1,x,"|");
    mvprintw(y+1,x+4,"|");
    mvprintw(y+2,x,"o---o");
}