#ifndef BATTLESHIP_PLAYER_H
#define BATTLESHIP_PLAYER_H

#include "Coordinate.h"

class Board;

class Player {
public:
    explicit Player(sf::RenderWindow *window, unsigned number);

    virtual ~Player();

    void update(sf::Vector2i mousePosWindow);

    void render(sf::RenderTarget *target);

    Board *getBoard() const;

    unsigned int getNumber() const;

private:
    sf::RenderWindow *window;
    Board *board;
    unsigned number;
};


#endif //BATTLESHIP_PLAYER_H
