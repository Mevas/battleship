#ifndef BATTLESHIP_PLAYER_H
#define BATTLESHIP_PLAYER_H


#include "Board.h"

class Player {
public:
    Player();
    virtual ~Player();

    void fire(Coordinate coords);
private:
    Board *board;
};


#endif //BATTLESHIP_PLAYER_H
