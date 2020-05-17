#include "../include/Globals.h"

const int globals::boardNumCells = 9;
const int globals::cellSize = 50;
const int globals::borderWidth = 1;
const int globals::boardSize = (cellSize) * globals::boardNumCells + (globals::boardNumCells + 1) * borderWidth;
const int globals::spaceBetweenBoards = 50;

const int globals::windowWidth = globals::boardSize;
const int globals::windowHeight = globals::boardSize * 2 + globals::spaceBetweenBoards;