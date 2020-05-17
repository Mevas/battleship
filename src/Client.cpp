//
// Created by tudor on 5/5/2020.
//

#include "../include/Constants.h"
#include "../include/Client.h"
#include "../include/Game.h"
#include <iostream>
#include <thread>

Client::Client()
{
    this->is_attacking = false;
    this->defendThread = nullptr;
    this->waitEnemyThread = nullptr;
}

Client & Client::getInstance()
{
    static Client    instance; // Guaranteed to be destroyed.
    // Instantiated on first use.
    return instance;
}

void Client::hostGame() {

    sf::Packet packet;

    sf::Uint16 x;
    std::string s;
    double d;

    //this->server = new Server();
    //this->serverIp = Server::getInstance().getServerIp();
    this->serverIp = "25.55.199.191";
    std::thread thListenHost(&Server::startListeningHost, &Server::getInstance());

    sf::Socket::Status status = socket.connect(this->serverIp, 53001);

    if(status != sf::Socket::Done) {
        std::cout << "Connection to server couldn't be make\n";
    }

    receivePacket(&packet);

    packet >> s;
    std::cout << s << std::endl;

    receivePacket(&packet);
    packet >> s;
    std::cout << s << std::endl;
    thListenHost.join();
}

bool Client::joinGame(sf::IpAddress serverIp) {
    sf::Packet packet;
    std::string s;

//    std::cout << "Server Ip?\n";
//    std::cin >> this->serverIp;
    this->serverIp = serverIp;
    sf::Socket::Status status = socket.connect(this->serverIp, 53001);

    if(status != sf::Socket::Done) {
        std::cout << "No Host for me:(\n";
        return false;
    }
    receivePacket(&packet);
    packet >> s;
    std::cout << s << std::endl;

    sf::Packet packetToSend;
    s = "I am your Guest!";
    packetToSend << s;
    sendPacket(&packet);
    return true;
    //playGame();
}

void Client::playGame() {
    sf::Packet packet;
    short serverMessage;
    receivePacket(&packet);
    packet >> serverMessage;
    std::cout << serverMessage << std::endl;
    if(serverMessage == SERVER_MSG_FIRST_MOVE) {
        this->is_attacking = true;
    } else {
        startDefendingThread();
    }

    std::cout << "Game finished!\n";
}

void Client::addShip(Coordinate head, unsigned length, Cardinals direction)
{
    sf::Packet addShipPacket;
    //TODO: add op packet << (and >>) overload on class Coordinate
    addShipPacket << CLIENT_SET_SHIP << head.X() << head.Y() << length << direction;
    sendPacket(&addShipPacket);
}

void Client::endShipPlacement() {
    sf::Packet endShipPlacementPacket;
    endShipPlacementPacket << CLIENT_ALL_SHIP_SET;
    sendPacket(& endShipPlacementPacket);
    this->waitEnemyThread = new std::thread([this] {
        playGame();
    });
}


void Client::Attack(Coordinate cell) {
    char cmd;
    sf::Packet packetToSend;
    //    std::cout << "Want to disconnect? (Y/N)\n";
    //    std::cin >> cmd;
//    if(cmd == 'Y') {
//        //TODO: Actually disconnect...
//        packetToSend << CLIENT_MSG_DISCONNECT;
//        sendPacket(&packetToSend);
//        return;
//    }
    packetToSend << CLIENT_ATTACK_COMMAND << cell.X() << cell.Y();
    sendPacket(&packetToSend);
}

void Client::Defend() {
    short serverMessage, messageLose;
    sf::Packet packetToReceive, losePacket;

    std::cout << "Now you are defending! Wait for enemy to attack.\n";
    receivePacket(&packetToReceive);
    packetToReceive >> serverMessage;
    std::cout << serverMessage << std::endl;
    switch(serverMessage) {
        case SERVER_MSG_END: {
            //TODO: disconnect...
            return;
        }
        case SERVER_HIT_RESOLVE: {
            HitTypes hit;
            short x, y;
            packetToReceive >> x >> y >> hit;
            playerShadow->mark(Coordinate(x, y), hit);

            std::cout << "You were hit at coord (" << x << ", " << y << "). It was a " << static_cast<int>(hit)
                      << std::endl;
            receivePacket(&losePacket);
            losePacket >> messageLose;
            if(messageLose == SERVER_MSG_LOSE)
            {
                std::cout << "You Lost. All your ship have sunken\n";
                //TODO: end the game
            }
            break;
        }
        default: {
            //TODO: check server connection...
        }
    }
}

//return something like  HitTypes? Dunno...I think it's better for client obj to take action
void Client::ResolveAttack() {
    short messageFromServer, messageWin;
    sf::Packet packetToReceive, winPacket;
    receivePacket(&packetToReceive);
    packetToReceive >> messageFromServer;
    switch(messageFromServer) {
        case SERVER_MSG_END: {
            std::cout << "server closed, end process...";
            //TODO: disconnect
            return;
        }
        case SERVER_ATTACK_RESOLVE: {
            HitTypes hit;
            short x, y;
            packetToReceive >> x >> y >> hit;
            enemyShadow->mark(Coordinate(x, y), hit);
            std::cout << "The attack at coord (" << x << ", " << y << ") was a " << static_cast<int>(hit) << std::endl;
            receivePacket(&winPacket);
            winPacket >> messageWin;
            if(messageWin == SERVER_MSG_WIN)
            {
                std::cout << "You won!!!! Congratulations.\n";
                //TODO: end the game
            }
            startDefendingThread();
            break;
        }
        default: {
            std::cout << "HUH??";
            //TODO: check server connection...
        }
    }

}

void Client::startDefendingThread(){
    this->is_attacking = false;
    this->defendThread = new std::thread([this] {
        Defend();
        is_attacking = true;
    });
}

void Client::startHeartbeatThread(){
    //a while here
    this->defendThread = new std::thread([this] {
        // TODO(maybe) make a packet send to server receive msg back
    });
}

bool Client::readyToAttack()
{
    if(defendThread == nullptr) {
        return false;
    }

    if(this->is_attacking == true) {
        this->defendThread->join();
        delete this->defendThread;
        this->defendThread = nullptr;
        if(this->waitEnemyThread != nullptr)
        {
            this->waitEnemyThread->join();
            delete this->waitEnemyThread;
            this->waitEnemyThread = nullptr;
        }

        return true;
    }

    return false;
}

void Client::sendPacket(sf::Packet *packet) {
    //std::cout << CLIENT_MESSAGE_PREFIX << "Sending package...\n";
    if(this->socket.send((*packet)) != sf::Socket::Done) {
        //std::cout << CLIENT_MESSAGE_PREFIX << "Can't Send Package to Server!\n";
        return;
    }

    //std::cout << CLIENT_MESSAGE_PREFIX << "Package Sent\n";
}

void Client::receivePacket(sf::Packet *packet) {
    //std::cout << CLIENT_MESSAGE_PREFIX << "Receiving package...\n";
    if(this->socket.receive((*packet)) != sf::Socket::Done) {
        //std::cout << CLIENT_MESSAGE_PREFIX << "Can't Receive Package from Server!\n";
        return;
    }

    //std::cout << CLIENT_MESSAGE_PREFIX << "Package Received\n";
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
