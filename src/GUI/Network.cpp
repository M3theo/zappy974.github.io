/*
** EPITECH PROJECT, 2025
** network
** File description:
** network
*/

#include "Network.hpp"

Zappy::Network::Network()
{
    _sock = std::make_shared<sf::TcpSocket>();
    std::cout << "[Network] Socket initialized" << std::endl;
}

Zappy::Network::~Network()
{
    if (_sock) {
        _sock->disconnect();
        std::cout << "[Network] Socket disconnected" << std::endl;
    }
}

void Zappy::Network::setBlocking(bool blocking)
{
    _sock->setBlocking(blocking);
}

bool Zappy::Network::sendMessage(std::string message)
{
    if (_sock->send(message.c_str(), message.size()) == sf::Socket::Done) {
        return true;
    } else {
        std::cerr << "[GUI] Failed to send message: " << message << std::endl;
        return false;
    }
}

sf::Socket::Status Zappy::Network::receiveMessage(std::array<char, 4096>& buffer, std::size_t& nbBytes)
{
    sf::Socket::Status status = _sock->receive(buffer.data(), buffer.size(), nbBytes);

    if (status == sf::Socket::NotReady)
        return sf::Socket::NotReady;
    return status;
}

bool Zappy::Network::connectToServer(const std::string &ip, int port, std::shared_ptr<sf::TcpSocket> sock)
{
    _sock = sock;
    sf::IpAddress ipp(ip);
    if (_sock->connect(ipp, port) != sf::Socket::Done) {
        std::cerr << "Connection failed" << std::endl;
        return false;
    }
    _sock->setBlocking(false);
    return true;
}
