#ifndef BATTLESHIP_PLAYER_H
#define BATTLESHIP_PLAYER_H


#include "Board.h"

class Player {
public:
    explicit Player(unsigned player);
    virtual ~Player();

    void fire(Coordinate coords);

    void update();

    void render(sf::RenderTarget *target);

private:
    Board *board;
    unsigned playerNumber;
};


#endif //BATTLESHIP_PLAYER_H
