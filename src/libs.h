#ifndef LIBS_H
#define LIBS_H

#include <ncurses.h>
#include <iostream>
#include <array>
#include <vector>
#include <cstdlib>
#include <ctime>

static inline void emergencyExit()
{
    endwin();
    exit(0);
}

#endif //LIBS_H