//
// Created by tudor on 5/5/2020.
//

#include "../include/Constants.h"
#include "../include/Client.h"

Client::Client() {
    this->is_attacking = false;
    this->won = false;
    this->lost = false;
    this->defendThread = nullptr;
    this->waitEnemyThread = nullptr;
}

bool Client::Won() const {
    return won;
}

bool Client::Lost() const {
    return lost;
}

Client &Client::getInstance() {
    static Client instance; // Guaranteed to be destroyed.
    // Instantiated on first use.
    return instance;
}

void Client::hostGame() {

    sf::Packet packet;

    std::string s;

    this->serverIp = Server::getInstance().getServerIp();
//    this->serverIp = "25.55.199.191";
    std::thread thListenHost(&Server::startListeningHost, &Server::getInstance());

    sf::Socket::Status status = socket.connect(this->serverIp, 53001);

    if(status != sf::Socket::Done) {
        std::cout << "Connection to server couldn't be made\n";
    }

    receivePacket(&packet);

    packet >> s;

    receivePacket(&packet);
    packet >> s;
    thListenHost.join();
}

bool Client::joinGame(sf::IpAddress serverIp) {
    sf::Packet packet;
    std::string s;

    this->serverIp = serverIp;
    sf::Socket::Status status = socket.connect(this->serverIp, 53001);

    if(status != sf::Socket::Done) {
        try {
            throw InvalidIPException();
        } catch(InvalidIPException &e) {
            std::cout << e.what();
            return false;
        }
    }
    receivePacket(&packet);
    packet >> s;

    sf::Packet packetToSend;
    s = "I am your Guest!";
    packetToSend << s;
    sendPacket(&packet);
    return true;
}

void Client::playGame() {
    sf::Packet packet;
    short serverMessage;
    receivePacket(&packet);
    packet >> serverMessage;
    if(serverMessage == SERVER_MSG_FIRST_MOVE) {
        this->is_attacking = true;
    } else {
        startDefendingThread();
    }
}

void Client::addShip(Coordinate head, unsigned length, Cardinals direction) {
    sf::Packet addShipPacket;
    addShipPacket << CLIENT_SET_SHIP << head << length << direction;
    sendPacket(&addShipPacket);
}

void Client::endShipPlacement() {
    sf::Packet endShipPlacementPacket;
    endShipPlacementPacket << CLIENT_ALL_SHIP_SET;
    sendPacket(&endShipPlacementPacket);
    this->waitEnemyThread = new std::thread([this] {
        playGame();
    });
}


void Client::Attack(Coordinate cell) {
    sf::Packet packetToSend;
    packetToSend << CLIENT_ATTACK_COMMAND << cell.X() << cell.Y();
    sendPacket(&packetToSend);
}

void Client::Defend() {
    short serverMessage, messageLose;
    sf::Packet packetToReceive, losePacket;

    receivePacket(&packetToReceive);
    packetToReceive >> serverMessage;
    switch(serverMessage) {
        case SERVER_MSG_END: {
            return;
        }
        case SERVER_HIT_RESOLVE: {
            HitTypes hit;
            short x, y;
            packetToReceive >> x >> y >> hit;
            playerShadow->mark(Coordinate(x, y), hit);

            receivePacket(&losePacket);
            losePacket >> messageLose;
            if(messageLose == SERVER_MSG_LOSE) {
                lost = true;
            }
            break;
        }
        default: {
            break;
        }
    }
}

void Client::ResolveAttack() {
    short messageFromServer, messageWin;
    sf::Packet packetToReceive, winPacket;
    receivePacket(&packetToReceive);
    packetToReceive >> messageFromServer;
    switch(messageFromServer) {
        case SERVER_MSG_END: {
            std::cout << "Server closed, ending process...";
            return;
        }
        case SERVER_ATTACK_RESOLVE: {
            HitTypes hit;
            short x, y;
            packetToReceive >> x >> y >> hit;
            enemyShadow->mark(Coordinate(x, y), hit);

            receivePacket(&winPacket);
            winPacket >> messageWin;
            if(messageWin == SERVER_MSG_WIN) {
                won = true;
            }
            startDefendingThread();
            break;
        }
        default: {
            try {
                throw ServerConnectionException();
            } catch(ServerConnectionException &e) {
                std::cout << e.what();
            }
        }
    }

}

void Client::startDefendingThread() {
    this->is_attacking = false;
    this->defendThread = new std::thread([this] {
        Defend();
        is_attacking = true;
    });
}

bool Client::readyToAttack() {
    if(defendThread == nullptr) {
        return false;
    }

    if(this->is_attacking == true) {
        this->defendThread->join();
        delete this->defendThread;
        this->defendThread = nullptr;
        if(this->waitEnemyThread != nullptr) {
            this->waitEnemyThread->join();
            delete this->waitEnemyThread;
            this->waitEnemyThread = nullptr;
        }

        return true;
    }

    return false;
}

void Client::sendPacket(sf::Packet *packet) {
    if(this->socket.send((*packet)) != sf::Socket::Done) {
        return;
    }
}

void Client::receivePacket(sf::Packet *packet) {
    if(this->socket.receive((*packet)) != sf::Socket::Done) {
        return;
    }
}

bool Client::getIsAttacking() const {
    return is_attacking.load();
}

void Client::setPlayerShadow(Shadow *playerShadow) {
    Client::playerShadow = playerShadow;
}

void Client::setEnemyShadow(Shadow *enemyShadow) {
    Client::enemyShadow = enemyShadow;
}
