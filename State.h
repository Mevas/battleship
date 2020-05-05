#ifndef BATTLESHIP_STATE_H
#define BATTLESHIP_STATE_H

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class State {
public:
    State();

    virtual ~State();

    virtual void update() = 0;

    virtual void render() = 0;

private:
    std::vector<sf::Texture> textures;
};


#endif //BATTLESHIP_STATE_H
