#include "../include/State.h"

State::State(sf::RenderWindow *window, std::stack<State *> &states) : states(states) {
    this->window = window;
    this->wantsToQuit = false;
    if(!this->font.loadFromFile("../fonts/Roboto-Regular.ttf")) {
        std::cout << "Could not load font files" << std::endl;
    }
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
