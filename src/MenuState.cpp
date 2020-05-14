#include "../include/MenuState.h"
#include "../include/GameState.h"

MenuState::MenuState(sf::RenderWindow *window, std::stack<State *> &states) : State(window, states) {
    background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    background.setFillColor(sf::Color(80, 80, 80, 255));

    hostBtn = new Button(sf::Vector2f(100, 100), sf::Vector2f(260, 50), font, "Host Game",
                         sf::Color(70, 70, 70, 255),
                         sf::Color(50, 50, 50, 255),
                         sf::Color(20, 20, 20, 255));

    joinBtn = new Button(sf::Vector2f(100, 200), sf::Vector2f(260, 50), font, "Join Game",
                         sf::Color(70, 70, 70, 255),
                         sf::Color(50, 50, 50, 255),
                         sf::Color(20, 20, 20, 255));

    exitBtn = new Button(sf::Vector2f(100, 820), sf::Vector2f(260, 50), font, "Exit",
                         sf::Color(70, 70, 70, 255),
                         sf::Color(50, 50, 50, 255),
                         sf::Color(20, 20, 20, 255));
}

MenuState::~MenuState() {
    delete hostBtn;
    delete joinBtn;
    delete exitBtn;
};

void MenuState::update(const double &deltaTime) {
    this->updateInput(deltaTime);
    this->updateMousePosition();
    this->updateButtons();
}

void MenuState::updateInput(const double &deltaTime) {
    this->checkForQuit();
}

void MenuState::render(sf::RenderTarget *target) {
    target->draw(background);
    hostBtn->render(target);
    joinBtn->render(target);
    exitBtn->render(target);
}

void MenuState::updateButtons() {
    hostBtn->update(static_cast<sf::Vector2f>(mousePosWindow));
    joinBtn->update(static_cast<sf::Vector2f>(mousePosWindow));
    exitBtn->update(static_cast<sf::Vector2f>(mousePosWindow));

    if(hostBtn->isPressed()) {
        std::cout << "Hosting" << std::endl;
        this->states.push(new GameState(this->window, this->states));
    }

    if(joinBtn->isPressed()) {
        std::cout << "Joining" << std::endl;
    }

    if(exitBtn->isPressed()) {
        this->wantsToQuit = true;
    }
}