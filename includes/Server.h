//
// Created by tudor on 5/5/2020.
//

#ifndef BATTLESHIP_CLIENT_SERVER_H
#define BATTLESHIP_CLIENT_SERVER_H
#include <SFML/Network.hpp>

class Server
{
private:
    sf::IpAddress serverIp;
    sf::TcpListener listener;
    sf::TcpSocket clientHost;
    sf::TcpSocket clientGuest;
public:
    Server();
    sf::IpAddress getServerIp();
    void startListeningHost();
    void acceptHost();
    void startListeningGuest();
    void acceptGuest();
};
#endif //BATTLESHIP_CLIENT_SERVER_H
