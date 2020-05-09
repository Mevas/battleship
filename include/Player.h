#ifndef BATTLESHIP_PLAYER_H
#define BATTLESHIP_PLAYER_H

#include "Coordinate.h"

class Board;

class Player {
public:
    explicit Player(sf::RenderWindow *window, unsigned number);

    virtual ~Player();

    void fire(Coordinate coords);

    void update(sf::RenderWindow *window, sf::Vector2i mousePosWindow);

    void render(sf::RenderTarget *target);

    Board *getBoard() const;

    sf::RenderWindow *getWindow() const;

    const sf::Vector2i &getMousePosWindow() const;

    unsigned int getNumber() const;

private:
    sf::RenderWindow *window;
    sf::Vector2i mousePosWindow;
    Board *board;
    unsigned number;
};


#endif //BATTLESHIP_PLAYER_H
