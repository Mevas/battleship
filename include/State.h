#ifndef BATTLESHIP_STATE_H
#define BATTLESHIP_STATE_H

#include <vector>
#include <stack>
#include <map>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class State {
public:
    explicit State(sf::RenderWindow *window, std::stack<State *> &states);

    virtual ~State();

    [[nodiscard]] const bool &getWantsToQuit() const;

    virtual void checkForQuit();

    virtual void update() = 0;

    virtual void updateInput() = 0;

    virtual void updateMousePosition();

    virtual void render(sf::RenderTarget *target) = 0;

protected:
    sf::RenderWindow *window;
    sf::Vector2i mousePosWindow;
    sf::Font font;
    bool wantsToQuit;
    std::stack<State *> &states;

};


#endif //BATTLESHIP_STATE_H
