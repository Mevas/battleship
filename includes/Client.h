//
// Created by tudor on 5/5/2020.
//

#ifndef BATTLESHIP_CLIENT_CLIENT_H
#define BATTLESHIP_CLIENT_CLIENT_H


#include <SFML/Network.hpp>
#include "Server.h"

class Client {
private:
    sf::TcpSocket socket;
    sf::IpAddress serverIp;
    Server * server;
public:
    void hostGame();
    void joinGame();
    void sendPacket(sf::Packet packet);
};


#endif //BATTLESHIP_CLIENT_CLIENT_H
