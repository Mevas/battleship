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

#include "Player.h"

class State {
public:
    explicit State(sf::RenderWindow *window);

    virtual ~State();

    [[nodiscard]] const bool &getWantsToQuit() const;

    virtual void checkForQuit();

    virtual void update(const double &deltaTime) = 0;

    virtual void updateKeybinds(const double &deltaTime) = 0;

    virtual void render(sf::RenderTarget *target) = 0;

private:
    sf::RenderWindow *window;
    std::vector<sf::Texture> textures;
    bool wantsToQuit;
};


#endif //BATTLESHIP_STATE_H
