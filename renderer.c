#include <stdio.h>
#include "renderer.h"
#include "board.h"

void init_rendering()
{
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    curs_set(0);  
    nodelay(stdscr, TRUE);

    init_color(COLOR_WHITE, 1000,1000,1000);
    init_color(8, 600,600,600);
    init_color(COLOR_BLUE, 0,0,1000);

    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_RED, COLOR_RED);
    init_pair(6, COLOR_WHITE, COLOR_BLACK);
    init_pair(7, COLOR_GREEN, COLOR_GREEN);
    init_pair(8, 8, COLOR_BLACK);
}



