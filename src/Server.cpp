//
// Created by tudor on 5/5/2020.
//
#include "../include/Constants.h"
#include "../include/Server.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>

Server::Server() {
    this->serverIp = sf::IpAddress::getLocalAddress();
    //this->serverIp = "82.76.175.95";
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
    short message;
    bool continueLoop = true;

    packetAttacker << SERVER_MSG_FIRST_MOVE;
    packetDefender << SERVER_MSG_SECOND_MOVE;
    sendPacket(attacker, &packetAttacker);
    sendPacket(defender, &packetDefender);
    packetAttacker.clear();
    packetDefender.clear();

    //TODO: change to loop
    while(continueLoop) {
        //receive msg from host
        receivePacket(attacker, &packetAttacker);
        packetAttacker >> message;
        switch(message) {
            case CLIENT_MSG_DISCONNECT: {
                //TODO: inform defender, prepare to close server, break game loop
                packetDefender << SERVER_MSG_END;
                sendPacket(defender, &packetDefender);
                continueLoop = false;
                break;
            }
            case CLIENT_ATTACK_COMMAND: {
                short x, y;
                bool shipHit = false;
                packetAttacker >> x >> y;
                packetAttacker.clear();
                //TODO: see if defender have boat at position (x, y), return message, now just a placeHolder
                packetAttacker << SERVER_ATTACK_RESOLVE << x << y << shipHit;
                packetDefender << SERVER_HIT_RESOLVE << x << y << shipHit;
                std::thread thMessageAttacker(&Server::sendPacket, this, attacker, &packetAttacker);
                sendPacket(defender, &packetDefender);
                thMessageAttacker.join();
                break;
            }
            default: {
                //TODO: check connection with attacker???, send defender w8 message, try again, prevent attacker/defender swap
                break;
            }
        }
        //swap attacker and defender
        packetAttacker.clear();
        packetDefender.clear();
        auto tmp = attacker;
        attacker = defender;
        defender = tmp;
    }

    //TODO: disconnect clients, close server...
}

void Server::sendPacket(sf::TcpSocket *client, sf::Packet *packet) {
    //std::cout << SERVER_MESSAGE_PREFIX << "Sending package...\n";
    if((*client).send((*packet)) != sf::Socket::Done) {
        //std::cout << SERVER_MESSAGE_PREFIX << "Can't Send Package to Client!\n";
        return;
    }

    //std::cout << SERVER_MESSAGE_PREFIX << "Package Sent\n";
}

void Server::receivePacket(sf::TcpSocket *client, sf::Packet *packet) {
    //std::cout << SERVER_MESSAGE_PREFIX << "Receiving package...\n";
    if((*client).receive((*packet)) != sf::Socket::Done) {
        //std::cout << SERVER_MESSAGE_PREFIX << "Can't Receive Package from Client!\n";
        return;
    }

    //std::cout << SERVER_MESSAGE_PREFIX << "Package Received\n";
}