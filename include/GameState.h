#ifndef BATTLESHIP_GAMESTATE_H
#define BATTLESHIP_GAMESTATE_H

#include "State.h"
#include "Player.h"

class GameState : public State {
public:
    explicit GameState(sf::RenderWindow *window, std::stack<State *> &states);

    ~GameState() override;

    void update(const double &deltaTime) override;

    void updateInput(const double &deltaTime) override;

    void render(sf::RenderTarget *target) override;

    Board *getClickedBoard() const;

    Player *getPlayer();

    Player *getEnemy();

    bool isPlacingShips() const;

private:
    Player *player;
    Player *enemy;
};


#endif //BATTLESHIP_GAMESTATE_H
