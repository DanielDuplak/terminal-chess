#include "greatest.h"

extern SUITE(test_move_handler);
extern SUITE(test_piece);
extern SUITE(test_game);

GREATEST_MAIN_DEFS();

int main(int argc, char **argv)
{
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(test_move_handler);
    RUN_SUITE(test_piece);
    RUN_SUITE(test_game);
    GREATEST_MAIN_END();
}
