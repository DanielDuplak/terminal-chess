#include "greatest.h"
#include <stdbool.h>
#include <stdlib.h>
#include "../piece.h"

// Test create_piece function
TEST test_create_piece()
{
    struct piece* new_piece = create_piece(PAWN, true);
    ASSERT(new_piece != NULL);
    ASSERT(new_piece->is_white == true);
    ASSERT(new_piece->type == PAWN);
    ASSERT(new_piece->move_list == NULL);
    ASSERT(new_piece->has_moved_two_spaces == false);
    destroy_piece(new_piece);
    PASS();
}

TEST test_destroy_piece()
{
    struct piece* piece = create_piece(KNIGHT, false);

    struct piece* result = destroy_piece(piece);
    ASSERT(result == NULL);
    PASS();
}

TEST test_clear_potential_moves()
{
    struct piece* piece = create_piece(KNIGHT, false);
    piece->move_list = create_move_list(NULL, 1, 2);
    create_move_list(piece->move_list, 3, 4);
    create_move_list(piece->move_list, 5, 6);

    struct move* result = clear_potential_moves(piece);
    ASSERT(result == NULL);
    ASSERT(piece->move_list == NULL);
    destroy_piece(piece);
    PASS();
}

// Test create_move_list function
TEST test_create_move_list()
{
    struct move* first = create_move_list(NULL, 1, 2);
    ASSERT(first != NULL);
    ASSERT(first->row == 1);
    ASSERT(first->col == 2);
    ASSERT(first->next == NULL);

    struct move* second = create_move_list(first, 3, 4);
    ASSERT(second != NULL);
    ASSERT(second->row == 3);
    ASSERT(second->col == 4);
    ASSERT(second->next == NULL);

    first->next = second;

    struct move* third = create_move_list(first, 5, 6);
    ASSERT(third != NULL);
    ASSERT(third->row == 5);
    ASSERT(third->col == 6);
    ASSERT(third->next == NULL);

    second->next = third;
    struct piece* piece = create_piece(ROOK, true);
    piece->move_list = first;

    destroy_piece(piece);

    PASS();
}


TEST test_remove_move()
{
    struct piece* piece = create_piece(KNIGHT, false);
    piece->move_list = create_move_list(NULL, 1, 2);
    create_move_list(piece->move_list, 3, 4);
    create_move_list(piece->move_list, 5, 6);

    struct move* current = piece->move_list;
    while(current != NULL)
    {
        if(current->row == 3 && current->col == 4)
        {
            remove_move(piece->move_list, current);
            break;
        }
        current = current->next;
    }

    struct move* current1 = piece->move_list;
    while(current1 != NULL)
    {
        ASSERT(current1->row != 3 && current1->col != 4);
        current1 = current1->next;
    }

    current1 = piece->move_list;
    while(current1 != NULL)
    {
        ASSERT(current1->row == 1 || current1->row == 5);
        ASSERT(current1->col == 2 || current1->col == 6);
        current1 = current1->next;
    }
    destroy_piece(piece);

    struct piece* piece2 = create_piece(KNIGHT, false);
    piece->move_list = create_move_list(NULL, 1, 2);
    piece2->move_list = remove_move(piece2->move_list, piece2->move_list);
    ASSERT(piece2->move_list == NULL);
    destroy_piece(piece2);

    PASS();
}

SUITE(test_piece)
{
    RUN_TEST(test_create_piece);
    RUN_TEST(test_destroy_piece);
    RUN_TEST(test_clear_potential_moves);
    RUN_TEST(test_create_move_list);
    RUN_TEST(test_remove_move);
}