#include "../include/Globals.h"

int globals::boardNumCells = 9;
int globals::cellSize = 50;
int globals::borderWidth = 1;
int globals::boardSize = (cellSize) * globals::boardNumCells + (globals::boardNumCells + 1) * borderWidth;
int globals::spaceBetweenBoards = 50;