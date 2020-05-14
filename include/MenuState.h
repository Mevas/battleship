#ifndef BATTLESHIP_MENUSTATE_H
#define BATTLESHIP_MENUSTATE_H


#include "State.h"
#include "Button.h"

class MenuState : public State {
public:
    explicit MenuState(sf::RenderWindow *window, std::stack<State *> &states);

    ~MenuState() override;

    void update(const double &deltaTime) override;

    void updateInput(const double &deltaTime) override;

    void updateButtons();

    void render(sf::RenderTarget *target) override;

private:
    sf::RectangleShape background;

    Button *hostBtn;
    Button *joinBtn;
    Button *exitBtn;
};


#endif //BATTLESHIP_MENUSTATE_H
