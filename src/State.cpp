#include "../include/State.h"

State::State(sf::RenderWindow *window) {
    this->window = window;
    this->wantsToQuit = false;
}

State::~State() = default;

void State::checkForQuit() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        this->wantsToQuit = true;
    }
}

const bool &State::getWantsToQuit() const {
    return this->wantsToQuit;
}

void State::updateMousePosition() {
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}
