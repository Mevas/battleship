#include <iostream>
#include "../include/Textbox.h"

Textbox::Textbox(sf::Vector2f position, sf::Vector2f size, sf::Font font, sf::Color color) {
    this->shape.setPosition(position);
    this->shape.setSize(size);
    shape.setFillColor(color);

    this->font = font;
    this->textbox.setFont(this->font);
    this->textbox.setFillColor(sf::Color::White);
    this->textbox.setCharacterSize(22);
    this->textbox.setPosition(
            this->shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) -
            this->textbox.getGlobalBounds().width / 2.f,
            this->shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) -
            this->textbox.getGlobalBounds().height / 2.f - 5
    );
}

Textbox::~Textbox() = default;

void Textbox::update(const sf::Vector2f mousePos) {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        isFocused = shape.getGlobalBounds().contains(mousePos);
        textbox.setString(text.str() + (isFocused ? "_" : ""));
    }
}

void Textbox::render(sf::RenderTarget *target) {
    this->textbox.setPosition(
            this->shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) -
            this->textbox.getGlobalBounds().width / 2.f,
            this->shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) -
            this->textbox.getGlobalBounds().height / 2.f - 5
    );

    target->draw(shape);
    target->draw(textbox);
}

void Textbox::inputLogic(int typedChar) {
    if(typedChar == DELETE_KEY) {
        if(text.str().length() <= 0) {
            return;
        }

        deleteLastChar();
        return;
    }

    if(typedChar == ENTER_KEY) {
        return;
    }

    if(typedChar == ESCAPE_KEY) {
        return;
    }

    text << static_cast<char>(typedChar);
    textbox.setString(text.str() + (isFocused ? "_" : ""));
}

void Textbox::deleteLastChar() {
    auto t = text.str().erase(text.str().length() - 1);

    text.str("");
    text << t;

    textbox.setString(text.str() + (isFocused ? "_" : ""));
}

std::string Textbox::getText() const {
    return text.str();
}

void Textbox::typedOn(sf::Event input) {
    if(isFocused) {
        int typedChar = input.text.unicode;
        if(typedChar < 128) {
            inputLogic(typedChar);
        }
    }
}

void Textbox::setIsFocused(bool focus) {
    this->isFocused = focus;
    textbox.setString(text.str().erase(text.str().length()));
}
