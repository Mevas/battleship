#ifndef BATTLESHIP_GAME_H
#define BATTLESHIP_GAME_H

#include "State.h"

class Game {
public:
    Game();

    virtual ~Game();

    void updateDeltaTime();

    void updateSFMLEvent();

    void update();

    void render();

    void run();

private:
    sf::RenderWindow *window;
    sf::Event event;

    sf::Clock deltaTimeClock;
    double deltaTime;

    void init();
};


#endif //BATTLESHIP_GAME_H
