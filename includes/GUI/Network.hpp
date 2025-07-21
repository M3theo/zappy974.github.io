/*
** EPITECH PROJECT, 2025
** network
** File description:
** network
*/

#ifndef NETWORK_HPP
    #define NETWORK_HPP

    #include <string>
    #include <iostream>
    #include <sstream>
    #include <memory>
    #include <SFML/Network.hpp>
    #include <array>

namespace Zappy
{
    class Network
    {
        public:
            //-----------CONSTRUCTOR-----------//
            Network();
            ~Network();

            //-----------CONNECTION-----------//
            bool connectToServer(const std::string &ip, int port, std::shared_ptr<sf::TcpSocket> sock);
            void setBlocking(bool blocking);

            //-----------COMMUNICATION-----------//
            bool sendMessage(std::string message);
            sf::Socket::Status receiveMessage(std::array<char, 4096>& buffer, std::size_t& nbBytes);

            //-----------GETTER-----------//
            std::shared_ptr<sf::TcpSocket> getSocket() const { return _sock; }

        private:
            std::shared_ptr<sf::TcpSocket> _sock;
            std::string _readBuffer;
    };
}

#endif /* !NETWORK_HPP */
