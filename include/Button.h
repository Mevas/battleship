#ifndef BATTLESHIP_BUTTON_H
#define BATTLESHIP_BUTTON_H

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <atomic>

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

    bool isPressed() const;

    void preventClicking();

private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font;

    sf::Color color;
    sf::Color hoverColor;
    sf::Color activeColor;

    ButtonStates state;
    std::atomic<bool> clicking_is_prevented {};
};


#endif //BATTLESHIP_BUTTON_H
