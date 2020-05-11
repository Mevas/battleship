#include "../include/MenuState.h"

MenuState::MenuState(sf::RenderWindow *window) : State(window) {
    background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    background.setFillColor(sf::Color(80, 80, 80, 255));
}

MenuState::~MenuState() {
};

void MenuState::update(const double &deltaTime) {
    this->updateInput(deltaTime);
    this->updateMousePosition();
}

void MenuState::updateInput(const double &deltaTime) {
    this->checkForQuit();
}

void MenuState::render(sf::RenderTarget *target) {
    target->draw(background);
}
