#include <memory>

#include "../include/GameState.h"
#include "../include/Board.h"
#include "../include/ShipFactory.h"
#include "../include/Client.h"
#include "../include/Globals.h"

GameState::GameState(sf::RenderWindow *window, std::stack<State *> &states) : State(window, states) {
    this->player = new Player(this->window, 2);
    this->enemy = new Player(this->window, 1);

    Client::getInstance().setPlayerShadow(this->player->getBoard()->getShadow());
    Client::getInstance().setEnemyShadow(this->enemy->getBoard()->getShadow());

    std::unique_ptr<ShipFactory> shipFactory = std::make_unique<ShipFactory>(*this->player->getBoard());

    this->player->getBoard()->addShip(shipFactory->createShip(ShipTypes::DESTROYER));
    this->player->getBoard()->addShip(shipFactory->createShip(ShipTypes::CRUISER));
    this->player->getBoard()->addShip(shipFactory->createShip(ShipTypes::SUBMARINE));
    this->player->getBoard()->addShip(shipFactory->createShip(ShipTypes::BATTLESHIP));
    this->player->getBoard()->addShip(shipFactory->createShip(ShipTypes::CARRIER));

    initText();
}

GameState::~GameState() {
    delete this->player;
    delete this->enemy;
}

void GameState::update() {
    this->updateInput();
    this->updateMousePosition();

    Client::getInstance().readyToAttack();

    if(Client::getInstance().Won()) {
        setCentralText("You've won!");
    } else if(Client::getInstance().Lost()) {
        setCentralText("You've lost!");
    } else {
        if(Client::getInstance().getIsAttacking()) {
            setCentralText("You're attacking!");
        } else {
            setCentralText("Enemy's attacking!");
        }
    }

    this->player->update(this->mousePosWindow);
    this->enemy->update(this->mousePosWindow);
}

void GameState::updateInput() {
    this->checkForQuit();
}

void GameState::render(sf::RenderTarget *target) {
    this->player->render(target);
    this->enemy->render(target);
    target->draw(text);
}

Player *GameState::getPlayer() {
    return player;
}

Player *GameState::getEnemy() {
    return enemy;
}

bool GameState::isPlacingShips() const {
    return !player->getBoard()->getHeldShips().empty();
}

void GameState::setCentralText(std::string text) {
    this->text.setString(text);
}

void GameState::initText() {
    this->textPlate.setPosition(sf::Vector2f(0, globals::boardSize));
    this->textPlate.setSize(sf::Vector2f(globals::windowWidth, globals::spaceBetweenBoards));
    textPlate.setFillColor(sf::Color::Black);

    this->text.setFont(font);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(22);
    this->text.setPosition(
            this->textPlate.getPosition().x + (textPlate.getGlobalBounds().width / 2.f) -
            this->text.getLocalBounds().width / 2.f - 90,
            this->textPlate.getPosition().y + (textPlate.getGlobalBounds().height / 2.f) -
            this->text.getLocalBounds().height / 2.f - 15
    );
}
