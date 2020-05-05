#include "GameState.h"

GameState::GameState(sf::RenderWindow *window) : State(window) {

}

GameState::~GameState() = default;

void GameState::update(const double &deltaTime) {
    this->updateKeybinds(deltaTime);
}

void GameState::updateKeybinds(const double &deltaTime) {
    this->checkForQuit();
}

void GameState::render(sf::RenderTarget *target) {

}
