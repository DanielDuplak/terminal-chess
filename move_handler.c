#include "move_handler.h"
#include <stdio.h>
#include <stdlib.h>


bool update_potential_moves(struct piece* board[BOARD_ROWS][BOARD_COLS], bool whites_turn, int row, int col)
{
    if(row < 0 || col < 0 || row >= BOARD_ROWS || col >= BOARD_COLS)
    {
        return false;
    }
    if(board[row][col] == NULL)
    {
        return false;
    }
    if(board[row][col]->is_white != whites_turn)
    {
        return false;
    }
    board[row][col]->move_list = clear_potential_moves(board[row][col]->move_list);

    bool found_move = false;
    
    switch(board[row][col]->type)
    {
    case PAWN:
        found_move = get_pawn_moves(board, whites_turn, row, col);
        break;
    case KNIGHT:
        found_move = get_knight_moves(board, row, col);
        break;
    case BISHOP:
        found_move = get_diagonal_moves(board, row, col);
        break;
    case ROOK:
        found_move = get_straight_moves(board, row, col);
        break;
    case QUEEN:
        found_move = (get_diagonal_moves(board, row, col) || get_straight_moves(board, row, col));
        break;
    case KING:
        found_move = get_king_moves(board, row, col);
        break;
    default:
        break;
    }
    if(found_move)
    {
        return try_potential_moves(board, whites_turn, row, col);
    }
    
    return false;
}

bool get_pawn_moves(struct piece* board[BOARD_ROWS][BOARD_COLS], bool whites_turn, int row, int col)
{
    bool found_moves = false;
    int direction = whites_turn ? -1 : 1;
    if(row + direction < 0 || row + direction >= BOARD_ROWS)
    {
        return false;
    }
    if(board[row + (direction * 2)][col] == NULL && ((row == 6 && whites_turn) || (row == 1 && !whites_turn)))
    {
        add_move_to_piece(board[row][col], row+(direction*2), col);
        found_moves = true;
    }
    if(board[row + direction][col] == NULL)
    {
        add_move_to_piece(board[row][col], row+direction, col);
        found_moves = true;
    }
    if(col-1 >= 0 && board[row + direction][col-1] != NULL && board[row + direction][col-1]->is_white != whites_turn)
    {
        add_move_to_piece(board[row][col], row+direction, col-1);
        found_moves = true;
    }
    if(col+1 < BOARD_COLS && board[row + direction][col+1] != NULL && board[row + direction][col+1]->is_white != whites_turn)
    {
        add_move_to_piece(board[row][col], row+direction, col+1);
        found_moves = true;
    }

    //en passant
    /*
    if(col - 1 >= 0 && board[row + direction][col - 1] == NULL && board[row][col-1] != NULL && board[row][col-1]->is_white != whites_turn && board[row][col-1]->has_moved_two_spaces)
    {
        add_move_to_piece(board[row][col], row+direction, col-1);
        found_moves = true;
    }
    if(col + 1 >= 0 && board[row + direction][col + 1] == NULL && board[row][col+1] != NULL && board[row][col+1]->is_white != whites_turn && board[row][col+1]->has_moved_two_spaces)
    {
        add_move_to_piece(board[row][col], row+direction, col+1);
        found_moves = true;
    }
    */
    return found_moves;
}

bool get_king_moves(struct piece* board[BOARD_ROWS][BOARD_COLS], int row, int col)
{
    bool found_moves = false;
    int moves[8][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

    for (int i = 0; i < 8; i++)
    {
        int new_row = row + moves[i][0];
        int new_col = col + moves[i][1];

        if (new_row >= 0 && new_row < BOARD_ROWS && new_col >= 0 && new_col < BOARD_COLS &&
            (board[new_row][new_col] == NULL || board[new_row][new_col]->is_white != board[row][col]->is_white))
        {
            add_move_to_piece(board[row][col], new_row, new_col);
            found_moves = true;
        }
    }

    return found_moves;
}

bool get_knight_moves(struct piece* board[BOARD_ROWS][BOARD_COLS], int row, int col)
{
    bool found_moves = false;
    int moves[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {-1, 2}, {1, 2}, {-1, -2}, {1, -2}};

    for (int i = 0; i < 8; i++)
    {
        int new_row = row + moves[i][0];
        int new_col = col + moves[i][1];

        if (new_row >= 0 && new_row < BOARD_ROWS && new_col >= 0 && new_col < BOARD_COLS &&
            (board[new_row][new_col] == NULL || board[new_row][new_col]->is_white != board[row][col]->is_white))
        {
            add_move_to_piece(board[row][col], new_row, new_col);
            found_moves = true;
        }
    }

    return found_moves;
}

bool get_diagonal_moves(struct piece* board[BOARD_ROWS][BOARD_COLS], int row, int col)
{
    bool found_moves = false;
    int directions[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    for(int i = 0; i < 4; i++)
    {
        int x = directions[i][0];
        int y = directions[i][1];
        int new_row = row + x;
        int new_col = col + y;

        while(new_row >= 0 && new_row < BOARD_ROWS && new_col >= 0 && new_col < BOARD_COLS)
        {
            if(board[new_row][new_col] == NULL || board[new_row][new_col]->is_white != board[row][col]->is_white)
            {
                add_move_to_piece(board[row][col], new_row, new_col);
                found_moves = true;
            }
            if(board[new_row][new_col] != NULL)
            {
                break;
            }
            new_row += x;
            new_col += y;
        }
    }
    return found_moves;
}

bool get_straight_moves(struct piece* board[BOARD_ROWS][BOARD_COLS], int row, int col)
{
    bool found_moves = false;
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    for(int i = 0; i < 4; i++)
    {
        int x = directions[i][0];
        int y = directions[i][1];
        int new_row = row + x;
        int new_col = col + y;

        while(new_row >= 0 && new_row < BOARD_ROWS && new_col >= 0 && new_col < BOARD_COLS)
        {
            if(board[new_row][new_col] == NULL || board[new_row][new_col]->is_white != board[row][col]->is_white)
            {
                add_move_to_piece(board[row][col], new_row, new_col);
                found_moves = true;
            }
            if(board[new_row][new_col] != NULL)
            {
                break;
            }
            new_row += x;
            new_col += y;
        }
    }
    return found_moves;
}

bool is_piece_in_check(struct piece* board[BOARD_ROWS][BOARD_COLS], int row, int col)
{
    int diagonal_directions[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    int straight_directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    for (int i = 0; i < 4; i++)
    {
        int dx = diagonal_directions[i][0];
        int dy = diagonal_directions[i][1];
        int new_row = row + dx;
        int new_col = col + dy;

        while (new_row >= 0 && new_row < BOARD_ROWS && new_col >= 0 && new_col < BOARD_COLS)
        {
            if (board[new_row][new_col] != NULL)
            {
                if (abs(new_col - col) <= 1 && abs(new_row - row) <= 1)
                {
                    if (board[new_row][new_col]->is_white != board[row][col]->is_white &&
                        (board[new_row][new_col]->type == PAWN || board[new_row][new_col]->type == KING))
                    {
                        return true;
                    }
                }
                if (board[new_row][new_col]->is_white != board[row][col]->is_white &&
                    (board[new_row][new_col]->type == QUEEN || board[new_row][new_col]->type == BISHOP))
                {
                    return true;
                }
                break;
            }
            new_row += dx;
            new_col += dy;
        }
    }


    for (int i = 0; i < 4; i++)
    {
        int dx = straight_directions[i][0];
        int dy = straight_directions[i][1];
        int new_row = row + dx;
        int new_col = col + dy;

        while (new_row >= 0 && new_row < BOARD_ROWS && new_col >= 0 && new_col < BOARD_COLS)
        {
            if (board[new_row][new_col] != NULL)
            {
                if (abs(new_col - col) <= 1 && abs(new_row - row) <= 1)
                {
                    if (board[new_row][new_col]->is_white != board[row][col]->is_white &&
                        (board[new_row][new_col]->type == PAWN || board[new_row][new_col]->type == KING))
                    {
                        return true;
                    }
                }
                if (board[new_row][new_col]->is_white != board[row][col]->is_white &&
                    (board[new_row][new_col]->type == QUEEN || board[new_row][new_col]->type == ROOK))
                {
                    return true;
                }
                break;
            }
            new_row += dx;
            new_col += dy;
        }
    }

    return false;
}

bool is_king_in_check(struct piece* board[BOARD_ROWS][BOARD_COLS], bool whites_turn)
{
    for(int row = 0; row < BOARD_ROWS; row++)
    {
        for(int col = 0; col < BOARD_COLS; col++)
        {
            if(board[row][col] != NULL && board[row][col]->is_white == whites_turn && board[row][col]->type == KING && is_piece_in_check(board, row, col))
            {
                return true; 
            }
        }
    }
    return false;
}

void add_move_to_piece(struct piece* piece, int row, int col)
{
    if(piece->move_list == NULL)
    {
        piece->move_list = create_move_list(NULL, row, col);
    }
    else
    {
        create_move_list(piece->move_list, row, col);
    }
}

bool try_potential_moves(struct piece* board[BOARD_ROWS][BOARD_COLS], bool whites_turn, int row, int col)
{
    if (board[row][col]->move_list == NULL)
    {
        return false;
    }
    struct move* current = board[row][col]->move_list;
    while (current != NULL)
    {
        struct piece* original_piece = board[row][col];
        struct piece* temp_piece = NULL;
        if (board[current->row][current->col] != NULL)
        {
            temp_piece = board[current->row][current->col];
        }
        board[current->row][current->col] = board[row][col];
        board[row][col] = NULL;
        if (is_king_in_check(board, whites_turn))
        {
            remove_move(board[current->row][current->col]->move_list, current);
        }
        board[row][col] = original_piece;
        board[current->row][current->col] = temp_piece;
        current = current->next;
    }
    return (board[row][col]->move_list != NULL) ? true : false;
}


//toto treba prerobit
bool move_piece(struct piece* board[BOARD_ROWS][BOARD_COLS], int cur_row, int cur_col, int row, int col)
{
    struct piece* piece = board[cur_row][cur_col];
    piece->has_moved_two_spaces = (piece->type == PAWN && abs(cur_row-row) == 2) ? true : false;
    if(piece == NULL)
    {
        return false;
    }
    if(piece->move_list == NULL)
    {
        return false;
    }
    struct move* current = piece->move_list;
    while(current != NULL)
    {
        if(current->row == row && current->col == col)
        {
            if(board[row][col] != NULL)
            {
                destroy_piece(board[row][col]);
            }
            board[row][col] = board[cur_row][cur_col];
            board[cur_row][cur_col] = NULL;
            return true;
        }
        current = current->next;
    }
    return false;
}
