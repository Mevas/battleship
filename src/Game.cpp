#include <iostream>
#include "../include/Game.h"
#include "../include/Globals.h"
#include "../include/Board.h"
#include "../include/Ship.h"
#include "../include/MenuState.h"

Game::Game() {
    this->init();
}

void Game::init() {
    this->initWindow();
    this->initStates();
}

void Game::initWindow() {
    this->window = new sf::RenderWindow(
            sf::VideoMode(globals::boardSize, globals::boardSize * 2 + globals::spaceBetweenBoards), "Battleship",
            sf::Style::Close);
    this->window->setFramerateLimit(165);
    this->window->setKeyRepeatEnabled(false);
}

void Game::initStates() {
    this->states.push(new MenuState(this->window, this->states));
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
        if(this->event.type == sf::Event::Closed) {
            this->window->close();
            end();
        }

        updateGameEvents();
        updateMenuEvents();
    }
}

void Game::updateGameEvents() {
    auto gameState = dynamic_cast<GameState *>(states.top());

    if(!gameState) {
        return;
    }

    if(this->event.type == sf::Event::KeyPressed) {
        if(event.key.code == sf::Keyboard::R) {
            auto heldShips = gameState->getPlayer()->getBoard()->getHeldShips();
            if(!heldShips.empty()) {
                heldShips.top()->rotate();
            }
        }
    }

    if(this->event.type == sf::Event::MouseButtonPressed) {
        if(event.mouseButton.button == sf::Mouse::Left) {
            if(gameState->isPlacingShips()) {
                gameState->getPlayer()->getBoard()->click();
            } else {
                gameState->getEnemy()->getBoard()->click();
            }
        }
    }
}

void Game::updateMenuEvents() {
    auto menuState = dynamic_cast<MenuState *>(states.top());

    if(!menuState) {
        return;
    }


}

void Game::update() {
    this->updateSFMLEvent();

    if(!this->states.empty()) {
        this->states.top()->update(this->deltaTime);

        if(this->states.top()->getWantsToQuit()) {
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
