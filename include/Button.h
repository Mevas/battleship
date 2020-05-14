#ifndef BATTLESHIP_BUTTON_H
#define BATTLESHIP_BUTTON_H

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

enum class ButtonStates {
    IDLE, HOVER, ACTIVE
};

class Button {
public:
    Button(sf::Vector2f position, sf::Vector2f size, sf::Font font, std::string text, sf::Color color,
           sf::Color hoverColor,
           sf::Color activeColor);

    ~Button();

    void update(const sf::Vector2f mousePos);

    void render(sf::RenderTarget *target);

    void setState(ButtonStates state);

    ButtonStates getState() const;

    bool isPressed() const;

private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font;

    sf::Color color;
    sf::Color hoverColor;
    sf::Color activeColor;

    ButtonStates state;
};


#endif //BATTLESHIP_BUTTON_H
