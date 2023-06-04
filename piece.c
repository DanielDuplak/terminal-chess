#include "piece.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


struct piece* create_piece(enum piece_type type, bool is_white, int pos_x, int pos_y)
{
    if(pos_x < 0 || pos_y < 0)
    {
        return NULL;
    }

    struct piece* new_piece = (struct piece*)malloc(sizeof(struct piece));
    if(new_piece == NULL)
    {
        return NULL;
    }
    new_piece->is_white = is_white;
    new_piece->type = type;
    new_piece->pos_x = pos_x;
    new_piece->pos_y = pos_y;
    new_piece->num_of_moves = 0;
    new_piece->potential_moves = NULL;

    return new_piece;
}

struct piece* destroy_piece(struct piece* piece)
{
    if(piece == NULL)
    {
        return NULL;
    }
    if(piece->potential_moves == NULL)
    {
        free(piece);
        piece = NULL;
        return NULL;
    }
    for(int i = 0; i < piece->num_of_moves; i++)
    {
        free(piece->potential_moves[i]);
    }
    free(piece->potential_moves);
    free(piece);
    piece = NULL;
    return NULL;
}


void clear_potential_moves(struct piece* piece)
{
    if(piece == NULL)
    {
        return;
    }
    if(piece->potential_moves == NULL)
    {
        return;
    }
    for(int i = 0; i < piece->num_of_moves; i++)
    {
        free(piece->potential_moves[i]);
    }
    free(piece->potential_moves);
    piece->potential_moves = NULL;
}