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
    struct move* move_list;
};

struct move
{
    int row;
    int col;
    struct move* next;
};


struct piece* create_piece(enum piece_type type, bool is_white);


struct piece* destroy_piece(struct piece* piece);


struct move* clear_potential_moves(struct move* first);


struct move* create_move_list(struct move* first, int row, int col);

struct move* remove_move(struct move* first, struct move* move_to_remove);
