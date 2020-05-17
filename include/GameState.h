#ifndef BATTLESHIP_GAMESTATE_H
#define BATTLESHIP_GAMESTATE_H

#include "State.h"
#include "Player.h"

class GameState : public State {
public:
    explicit GameState(sf::RenderWindow *window, std::stack<State *> &states);

    ~GameState() override;

    void update() override;

    void updateInput() override;

    void render(sf::RenderTarget *target) override;

    Board *getClickedBoard() const;

    Player *getPlayer();

    Player *getEnemy();

    bool isPlacingShips() const;

    void setCentralText(std::string text);

    void initText();

private:
    Player *player;
    Player *enemy;

    sf::RectangleShape textPlate;
    sf::Text text;
};


#endif //BATTLESHIP_GAMESTATE_H
