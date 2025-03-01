#ifndef INTERFACE_H
#define INTERFACE_H

#include <ncurses.h>
#include <stdlib.h>

#include "../../gameInfo.h"

void render(GameInfo_t info);
void terminateGame();

#endif