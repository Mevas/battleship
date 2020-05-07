#include "../include/GameState.h"

GameState::GameState(sf::RenderWindow *window) : State(window) {
    this->player1 = new Player(1);
    this->player2 = new Player(2);
}

GameState::~GameState() {
    delete this->player1;
    delete this->player2;
};

void GameState::update(const double &deltaTime) {
    this->updateKeybinds(deltaTime);
    this->player1->update(this->window);
    this->player2->update(this->window);
}

void GameState::updateKeybinds(const double &deltaTime) {
    this->checkForQuit();
}

void GameState::render(sf::RenderTarget *target) {
    this->player1->render(target);
    this->player2->render(target);
}
