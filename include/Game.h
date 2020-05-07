#ifndef BATTLESHIP_GAME_H
#define BATTLESHIP_GAME_H

#include "GameState.h"

class Game {
public:
    Game();

    virtual ~Game();

    void updateDeltaTime();

    void updateSFMLEvent();

    void update();

    void render();

    void run();

    void end();
private:
    sf::RenderWindow *window;
    sf::Event event;

    sf::Clock deltaTimeClock;
    double deltaTime;

    std::stack<State *> states;

    void init();
    void initWindow();
    void initStates();
};


#endif //BATTLESHIP_GAME_H