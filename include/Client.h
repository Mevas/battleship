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
    std::thread *defendThread;
    std::atomic<bool> is_attacking{};
    Shadow *playerShadow;
    Shadow *enemyShadow;

    Client();

public:
    static Client &getInstance();

    Client(Client const &) = delete;

    void operator=(Client const &) = delete;

    void hostGame();

    void joinGame();

    void playGame();

    void Attack(Coordinate cell);

    void Defend();

    void ResolveAttack();

    void startDefendingThread();
    ///
    /// \return true if defendThread is finished
    bool readyToAttack();

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
