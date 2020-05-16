//
// Created by tudor on 5/5/2020.
//

#ifndef BATTLESHIP_CLIENT_CLIENT_H
#define BATTLESHIP_CLIENT_CLIENT_H


#include <SFML/Network.hpp>
#include <thread>
#include <atomic>
#include "Server.h"
#include "Shadow.h"

class Client {
private:
    sf::TcpSocket socket;
    sf::IpAddress serverIp;
    std::thread * defendThread;
    std::atomic<bool> is_attacking {};
    Shadow *playerShadow;
    Shadow *enemyShadow;

    Client();

public:
    static Client &getInstance();

    Client(Client const &) = delete;

    void operator=(Client const &) = delete;

    void hostGame();

    bool joinGame(sf::IpAddress serverIp);

    void playGame();

    void addShip(Coordinate head, unsigned length, Cardinals direction);

    void endShipPlacement();

    void Attack(Coordinate cell);

    void Defend();

    void ResolveAttack();

    void startDefendingThread();

    ///
    ///every HEARTBEAT_RATE, send the server your connection status and receive server status
    void startHeartbeatThread();

    ///
    /// \return true if defendThread is finished
    bool readyToAttack();

    bool readyToStartGame();

    ///
    /// \param packet , address of the packet used to send data to server
    void sendPacket(sf::Packet *packet);

    ///
    /// \param packet , address of the packet used to receive data from server
    void receivePacket(sf::Packet *packet);

    bool getIsAttacking() const;

    void setPlayerShadow(Shadow *playerShadow);

    void setEnemyShadow(Shadow *enemyShadow);
};


#endif //BATTLESHIP_CLIENT_CLIENT_H
