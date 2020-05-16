//
// Created by tudor on 5/5/2020.
//
#include "../include/Constants.h"
#include "../include/Server.h"
#include <iostream>
#include <thread>

Server::Server() {
    this->serverIp = sf::IpAddress::getLocalAddress();
    //this->serverIp = "82.76.175.95";
    this->hostBoard = new ServerBoard();
    this->guestBoard = new ServerBoard();
    std::cout << this->serverIp << std::endl;
}

Server & Server::getInstance()
{
    static Server    instance; // Guaranteed to be destroyed.
    // Instantiated on first use.
    return instance;
}

sf::IpAddress Server::getServerIp() {
    return this->serverIp;
}

void Server::startListeningHost() {
    if(this->listener.listen(53001) != sf::Socket::Done) {
        //std::cout << "Can't start listening host!\n";
    } else {
        //std::cout << "Now I Listen for Host!\n";
        acceptHost();
    }
}

void Server::acceptHost() {
    if(listener.accept(this->clientHost) != sf::Socket::Done) {
        //std::cout << "Couldn't accept host\n";
        return;
    }

    std::string s = "hello, Host";

    sf::Packet packet;
    packet << s;

    sendPacket(&clientHost, &packet);

    startListeningGuest();
}

void Server::startListeningGuest() {
    if(this->listener.listen(53002) != sf::Socket::Done) {
        //std::cout << "Can't start listening guest!\n";
    } else {
        //std::cout << "Now I Listen for Guest!\n";
        acceptGuest();
    }
}

void Server::acceptGuest() {
    if(listener.accept(this->clientGuest) != sf::Socket::Done) {
        //std::cout << "Couldn't accept guest\n";
        return;
    }

    std::string s = "hello, Guest";

    sf::Packet packet;
    sf::Packet packetToReceive;
    sf::Packet packetToSend;
    packet << s;

    sendPacket(&clientGuest, &packet);
    receivePacket(&clientGuest, &packetToReceive);

    packetToReceive >> s;
    packetToSend << s;
    sendPacket(&clientHost, &packetToSend);
}

void Server::gameLoop() {
    sf::Packet packetAttacker;
    sf::Packet packetDefender;
    //TODO: randomize first move
    sf::TcpSocket *attacker = &this->clientHost;
    sf::TcpSocket *defender = &this->clientGuest;
    ServerBoard *attackerBoard = this->hostBoard;
    ServerBoard *defenderBoard = this->guestBoard;

    packetAttacker << SERVER_MSG_FIRST_MOVE;
    packetDefender << SERVER_MSG_SECOND_MOVE;
    sendPacket(attacker, &packetAttacker);
    sendPacket(defender, &packetDefender);
    packetAttacker.clear();
    packetDefender.clear();

    std::thread thHostPlaceBoard([this] {
        sf::Packet packetHost;
        short shipHeadX, shipHeadY;
        unsigned shipLength;
        Cardinals shipDirection;
        short msgHost;

        while(true) {
            receivePacket(&clientHost, &packetHost);
            packetHost >> msgHost;
            if (msgHost == CLIENT_ALL_SHIP_SET) {
                break;
            }
            else if(msgHost != CLIENT_SET_SHIP){
                //dunno extend std::exception i guess...
                std::cout << "Host Add ship operation failed!";
                continue;
            }
            packetHost >> shipHeadX >> shipHeadY >> shipLength >> shipDirection;
            Coordinate shipHead(shipHeadX, shipHeadY);
            hostBoard->addShip(shipHead, shipLength, shipDirection);
        }
    });

    std::thread thGuestPlaceBoard([this] {
        sf::Packet packetHost;
        short shipHeadX, shipHeadY;
        unsigned shipLength;
        Cardinals shipDirection;
        short msgHost;

        while(true) {
            receivePacket(&clientGuest, &packetHost);
            packetHost >> msgHost;
            if (msgHost == CLIENT_ALL_SHIP_SET) {
                break;
            }
            else if(msgHost != CLIENT_SET_SHIP){
                //dunno
                std::cout << "Guest Add ship operation failed!";
                continue;
            }
            packetHost >> shipHeadX >> shipHeadY >> shipLength >> shipDirection;
            Coordinate shipHead(shipHeadX, shipHeadY);
            guestBoard->addShip(shipHead, shipLength, shipDirection);
        }
    });

    thHostPlaceBoard.join();
    thGuestPlaceBoard.join();

    short message;
    bool continueLoop = true;

    //TODO: change to loop
    while(continueLoop) {
        //receive msg from host
        receivePacket(attacker, &packetAttacker);
        packetAttacker >> message;
        switch(message) {
            case CLIENT_MSG_DISCONNECT: {
                //TODO: inform defender, prepare to close server, break game loop
                //packetDefender << SERVER_MSG_END;
                //sendPacket(defender, &packetDefender);
                continueLoop = false;
                break;
            }
            case CLIENT_ATTACK_COMMAND: {
                short x, y;
                packetAttacker >> x >> y;
                packetAttacker.clear();
                HitTypes hit = defenderBoard->attack(Coordinate(x, y));
                std::cout << static_cast<int>(hit);
                packetAttacker << SERVER_ATTACK_RESOLVE << x << y << hit;
                packetDefender << SERVER_HIT_RESOLVE << x << y << hit;
                sendPacket(attacker, &packetAttacker, true);
                sendPacket(defender, &packetDefender, true);
                if(defenderBoard->getShipCount() == 0)
                {
                    packetAttacker << SERVER_MSG_WIN;
                    packetDefender << SERVER_MSG_LOSE;
                    sendPacket(attacker, &packetAttacker, true);
                    sendPacket(defender, &packetDefender, true);
                    continueLoop = false;
                } else {
                    packetAttacker << SERVER_MSG_EMPTY;
                    packetDefender << SERVER_MSG_EMPTY;
                    sendPacket(attacker, &packetAttacker, true);
                    sendPacket(defender, &packetDefender, true);
                }
                break;
            }
            default: {
                //TODO: check connection with attacker???, send defender w8 message, try again, prevent attacker/defender swap
                break;
            }
        }
        //swap attacker and defender
        //packetAttacker.clear();
        //packetDefender.clear();
        auto tmp = attacker;
        attacker = defender;
        defender = tmp;
        auto tmpBoard = attackerBoard;
        attackerBoard = defenderBoard;
        defenderBoard = tmpBoard;
    }

    //TODO: disconnect clients, close server...
}

void Server::sendPacket(sf::TcpSocket *client, sf::Packet *packet, bool clear) {
    //std::cout << SERVER_MESSAGE_PREFIX << "Sending package...\n";
    if((*client).send((*packet)) != sf::Socket::Done) {
        //std::cout << SERVER_MESSAGE_PREFIX << "Can't Send Package to Client!\n";
        return;
    }

    //std::cout << SERVER_MESSAGE_PREFIX << "Package Sent\n";

    if(clear)
        (*packet).clear();
}

void Server::receivePacket(sf::TcpSocket *client, sf::Packet *packet) {
    //std::cout << SERVER_MESSAGE_PREFIX << "Receiving package...\n";
    if((*client).receive((*packet)) != sf::Socket::Done) {
        //std::cout << SERVER_MESSAGE_PREFIX << "Can't Receive Package from Client!\n";
        return;
    }

    //std::cout << SERVER_MESSAGE_PREFIX << "Package Received\n";
}