#ifndef BATTLESHIP_GAME_H
#define BATTLESHIP_GAME_H

#include "GameState.h"
#include "Client.h"

class Game {
public:
    Game();

    virtual ~Game();

    void updateSFMLEvent();

    void updateGameEvents();

    void updateMenuEvents();

    void update();

    void render();

    void run();

    void end();

private:

    sf::RenderWindow *window;
    sf::Event event;

    std::stack<State *> states;

    void init();
    void initWindow();
    void initStates();
};


#endif //BATTLESHIP_GAME_H
