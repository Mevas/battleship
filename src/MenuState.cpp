#include "../include/MenuState.h"
#include "../include/GameState.h"
#include "../include/Client.h"

MenuState::MenuState(sf::RenderWindow *window, std::stack<State *> &states) : State(window, states) {
    ready_for_next_state = false;
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

    ipTextbox = new Textbox(sf::Vector2f(100, 250), sf::Vector2f(260, 50), font, sf::Color(74, 74, 74, 255));
}

MenuState::~MenuState() {
    if(hostThread != nullptr) {
        hostThread->join();
    }
    delete hostBtn;
    delete joinBtn;
    delete exitBtn;
    delete ipTextbox;
    delete hostThread;
}

void MenuState::update() {
    this->updateInput();
    this->updateMousePosition();
    this->updateButtons();
    if(this->ready_for_next_state) {
        this->hostThread->join();
        delete this->hostThread;
        this->hostThread = new std::thread([] {
            std::thread thGameLoop(&Server::gameLoop, &Server::getInstance());
            thGameLoop.join();
        });
        this->ready_for_next_state = false;
        this->states.push(new GameState(this->window, this->states));

    }
}

void MenuState::updateInput() {
    this->checkForQuit();
}

void MenuState::render(sf::RenderTarget *target) {
    target->draw(background);
    hostBtn->render(target);
    joinBtn->render(target);
    exitBtn->render(target);
    ipTextbox->render(target);
}

void MenuState::updateButtons() {
    hostBtn->update(static_cast<sf::Vector2f>(mousePosWindow));
    joinBtn->update(static_cast<sf::Vector2f>(mousePosWindow));
    exitBtn->update(static_cast<sf::Vector2f>(mousePosWindow));
    ipTextbox->update(static_cast<sf::Vector2f>(mousePosWindow));

//    Menu buttons
    if(hostBtn->isPressed()) {
        std::cout << "Hosting" << std::endl;
        this->hostThread = new std::thread([this] {
            Client::getInstance().hostGame();
            this->ready_for_next_state = true;
        });
        hostBtn->preventClicking();
        joinBtn->preventClicking();
    }

    if(joinBtn->isPressed()) {
        std::cout << "Joining" << std::endl;
        bool joined = Client::getInstance().joinGame(ipTextbox->getText());
        if(joined) {
            this->states.push(new GameState(this->window, this->states));
        }
    }

    if(exitBtn->isPressed()) {
        this->wantsToQuit = true;
    }
}

Textbox *MenuState::getIpTextbox() const {
    return ipTextbox;
}

