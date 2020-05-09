#ifndef BATTLESHIP_PLAYER_H
#define BATTLESHIP_PLAYER_H


#include "Board.h"

class Player {
public:
    explicit Player(sf::RenderWindow *window, unsigned player);

    virtual ~Player();

    void fire(Coordinate coords);

    void update(sf::RenderWindow *window, sf::Vector2i mousePosWindow);

    void render(sf::RenderTarget *target);

    Board *getBoard();

private:
    sf::RenderWindow *window;
    sf::Vector2i mousePosWindow;
    Board *board;
    unsigned playerNumber;
};


#endif //BATTLESHIP_PLAYER_H
