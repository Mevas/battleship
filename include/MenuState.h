#ifndef BATTLESHIP_MENUSTATE_H
#define BATTLESHIP_MENUSTATE_H


#include "State.h"

class MenuState : public State {
public:
    explicit MenuState(sf::RenderWindow *window);

    ~MenuState() override;

    void update(const double &deltaTime) override;

    void updateInput(const double &deltaTime) override;

    void render(sf::RenderTarget *target) override;

private:
    sf::RectangleShape background;
};


#endif //BATTLESHIP_MENUSTATE_H
