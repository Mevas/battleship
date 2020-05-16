#include <iostream>
#include "../include/Button.h"

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Font font, std::string text, sf::Color color,
               sf::Color hoverColor, sf::Color activeColor) {
    this->state = ButtonStates::IDLE;
    this->clicking_is_prevented = false;
    this->shape.setPosition(position);
    this->shape.setSize(size);

    this->font = font;
    this->text.setFont(this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(22);
    this->text.setPosition(
            this->shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) -
            this->text.getGlobalBounds().width / 2.f,
            this->shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) -
            this->text.getGlobalBounds().height / 2.f - 5
    );


    this->color = color;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;

    this->shape.setFillColor(color);
}

Button::~Button() {

}

void Button::update(const sf::Vector2f mousePos) {
    state = ButtonStates::IDLE;
    if(shape.getGlobalBounds().contains(mousePos)) {
        state = ButtonStates::HOVER;
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            state = ButtonStates::ACTIVE;
        }
    }
}

void Button::render(sf::RenderTarget *target) {
    switch(state) {
        case ButtonStates::IDLE:
            shape.setFillColor(color);
            break;
        case ButtonStates::HOVER:
            shape.setFillColor(hoverColor);
            break;
        case ButtonStates::ACTIVE:
            shape.setFillColor(activeColor);
            break;
    }

    target->draw(shape);
    target->draw(text);
}

ButtonStates Button::getState() const {
    return state;
}

bool Button::isPressed() const {
    if(this->clicking_is_prevented)
        return false;
    return state == ButtonStates::ACTIVE;
}

void Button::setState(ButtonStates state) {
    Button::state = state;
}

void Button::preventClicking()
{
    this->clicking_is_prevented = true;
}
