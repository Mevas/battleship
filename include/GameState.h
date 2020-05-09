#ifndef BATTLESHIP_GAMESTATE_H
#define BATTLESHIP_GAMESTATE_H

#include "State.h"
#include "Player.h"

class GameState : public State {
public:
    explicit GameState(sf::RenderWindow *window);

    ~GameState() override;

    void update(const double &deltaTime) override;

    void updateInput(const double &deltaTime) override;

    void render(sf::RenderTarget *target) override;

private:
    Player *player1;
    Player *player2;
};


#endif //BATTLESHIP_GAMESTATE_H
