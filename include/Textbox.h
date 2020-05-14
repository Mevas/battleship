#ifndef BATTLESHIP_TEXTBOX_H
#define BATTLESHIP_TEXTBOX_H

#include <sstream>
#include <SFML/Graphics.hpp>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox {
public:
    Textbox(sf::Vector2f position, sf::Vector2f size, sf::Font font, sf::Color color);

    ~Textbox();

    std::string getText() const;

    void update(const sf::Vector2f mousePos);

    void render(sf::RenderTarget *target);

    void typedOn(sf::Event input);

    void setIsFocused(bool isFocused);

private:
    sf::Text textbox;
    std::ostringstream text;
    sf::RectangleShape shape;
    sf::Font font;
    bool isFocused;

    void inputLogic(int typedChar);

    void deleteLastChar();
};


#endif //BATTLESHIP_TEXTBOX_H
