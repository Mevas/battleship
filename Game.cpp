#include <iostream>
#include "Game.h"

void Game::init() {
    this->window = new sf::RenderWindow(sf::VideoMode(640, 480), "Battleship");
}

Game::Game() {
    this->init();
}

Game::~Game() {
    delete this->window;
}

void Game::updateSFMLEvent() {
    while(this->window->pollEvent(event)) {
        if(this->event.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::update() {
    this->updateSFMLEvent();
}

void Game::render() {
    this->window->clear();
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
