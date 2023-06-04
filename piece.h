#include "game.h"
#include <stdbool.h>
#include <stdlib.h>


enum piece_type
{
    PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING
};

struct piece
{
    enum piece_type type;
    bool is_white;
    int** potential_moves;
    int num_of_moves;
};


struct piece* create_piece(enum piece_type type, bool is_white);


struct piece* destroy_piece(struct piece* piece);


void clear_potential_moves(struct piece* piece);
