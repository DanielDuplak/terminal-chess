#include "piece.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


struct piece* create_piece(enum piece_type type, bool is_white)
{

    struct piece* new_piece = (struct piece*)malloc(sizeof(struct piece));
    if(new_piece == NULL)
    {
        return NULL;
    }
    new_piece->is_white = is_white;
    new_piece->type = type;
    new_piece->move_list = NULL;

    return new_piece;
}

struct piece* destroy_piece(struct piece* piece)
{
    if(piece == NULL)
    {
        return NULL;
    }
    if(piece->move_list == NULL)
    {
        free(piece);
        piece = NULL;
        return NULL;
    }
    piece->move_list = clear_potential_moves(piece->move_list);
    free(piece);
    piece = NULL;
    return NULL;
}


struct move* clear_potential_moves(struct move* first)
{
    if(first == NULL)
    {
        return NULL;
    }
    while(first != NULL)
    {
        struct move* next = first->next;
        free(first);
        first = next;
    }
    return NULL;
}

struct move* create_move_list(struct move* first, int row, int col)
{
    struct move* new_move = (struct move*) malloc(sizeof(struct move));
    if(new_move == NULL)
    {
        return NULL;
    }
    new_move->row = row;
    new_move->col = col;
    if(first == NULL)
    {
        return new_move;
    }
    struct move* temp = first;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = new_move;
    return new_move;
}

struct move* remove_move(struct move* first, struct move* move_to_remove)
{
    if(first == NULL)
    {
        return NULL;
    }
    if(move_to_remove == NULL)
    {
        return NULL;
    }

    struct move* current = first;
    struct move* prev = NULL;
    
    while(current != NULL)
    {
        if(current == move_to_remove)
        {
            if(prev != NULL)
            {
                prev->next = current->next;
            }
            else
            {
                first = current->next;
            }
            free(current);
            return first;
        }
        prev = current;
        current = current->next;
    }
    return first;
}