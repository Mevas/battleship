#ifndef BATTLESHIP_MENUSTATE_H
#define BATTLESHIP_MENUSTATE_H


#include <thread>
#include <atomic>
#include "State.h"
#include "Button.h"
#include "Textbox.h"

class MenuState : public State {
public:
    explicit MenuState(sf::RenderWindow *window, std::stack<State *> &states);

    ~MenuState() override;

    void update() override;

    void updateInput() override;

    void updateButtons();

    void render(sf::RenderTarget *target) override;

    Textbox *getIpTextbox() const;

private:
    sf::RectangleShape background;

    Button *hostBtn;
    Button *joinBtn;
    Button *exitBtn;

    Textbox *ipTextbox;
    std::thread * hostThread;
    std::atomic<bool> ready_for_next_state {};
};


#endif //BATTLESHIP_MENUSTATE_H
