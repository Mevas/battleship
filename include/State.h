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
    explicit State(sf::RenderWindow *window);

    virtual ~State();

    [[nodiscard]] const bool &getWantsToQuit() const;

    virtual void checkForQuit();

    virtual void update(const double &deltaTime) = 0;

    virtual void updateKeybinds(const double &deltaTime) = 0;

    virtual void render(sf::RenderTarget *target) = 0;

protected:
    sf::RenderWindow *window;

private:
    std::vector<sf::Texture> textures;
    bool wantsToQuit;
};


#endif //BATTLESHIP_STATE_H
