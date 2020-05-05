#include <iostream>
#include "../include/Game.h"

Game::Game() {
    this->init();
}

void Game::init() {
    this->initWindow();
    this->initStates();
}

void Game::initWindow() {
    this->window = new sf::RenderWindow(sf::VideoMode(460, 970), "Battleship");
}

void Game::initStates() {
    this->states.push(new GameState(this->window));
}

Game::~Game() {
    delete this->window;

    while(!this->states.empty()) {
        delete this->states.top();
        this->states.pop();
    }
}

void Game::updateSFMLEvent() {
    while(this->window->pollEvent(event)) {
        if(this->event.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::update() {
    this->updateSFMLEvent();

    if(!this->states.empty()) {
        this->states.top()->update(this->deltaTime);

        if (this->states.top()->getWantsToQuit()) {
            delete this->states.top();
            this->states.pop();
        }
    } else {
        this->end();
        this->window->close();
    }
}

void Game::render() {
    this->window->clear();

    if(!this->states.empty()) {
        this->states.top()->render(this->window);
    }

    this->window->display();
}

void Game::run() {
    while(this->window->isOpen()) {
        this->updateDeltaTime();

        this->update();
        this->render();
    }
}

void Game::updateDeltaTime() {
    this->deltaTime = this->deltaTimeClock.restart().asSeconds();
}

void Game::end() {
    std::cout << "Goodbye...";
}
