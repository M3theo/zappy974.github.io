/*
** EPITECH PROJECT, 2025
** Parseserver
** File description:
** Header for the ParseServer class
*/

#ifndef PARSESERVER_HPP
    #define PARSESERVER_HPP

    #include <string>
    #include <map>
    #include <vector>
    #include <memory>
    #include <functional>
    #include <utility>
    #include <iostream>
    #include <sstream>
    #include <algorithm>
    #include <unistd.h>
    #include <cstring>
    #include <SFML/Network.hpp>
    #include "Tile.hpp"
    #include "Player.hpp"
    #include "Network.hpp"

namespace Zappy
{
    class ParseServer
    {
        public:
            //----------------- CONSTRUCTOR -----------------//
            ParseServer(std::shared_ptr<sf::TcpSocket> sock, std::shared_ptr<Zappy::Network> network);

            //----------------- GETTERS -----------------//
            inline int getMapWidth() const { return _mapWidth; }
            inline int getMapHeight() const { return _mapHeight; }
            inline bool isMapReady() const { return _mapWidth > 0 && _mapHeight > 0 && !_tiles.empty(); }
            inline const std::map<std::pair<int, int>, Tile>& getTiles() const { return _tiles; }
            inline const std::map<int, std::shared_ptr<Player>>& getPlayers() const { return _players; }

            //----------------- CONTROL -----------------//
            inline void start() { _running = true; }
            inline void stop() { _running = false; }

            //----------------- MAIN LOOP -----------------//
            void run();

            //----------------- NETWORK AND PARSING -----------------//
            void getCommand();
            void sendCommands();
            std::string getResourceName(int id);
            std::vector<std::string> split(const std::string &line);
            void processCommand(const std::string& rawCommand);
            void initCommandMap();

            //----------------- COMMAND HANDLERS GRAPHIC-----------------//
            void handleMsz(const std::vector<std::string>& args);
            void handleBct(const std::vector<std::string>& args);
            void handleMct(const std::vector<std::string>& args);
            void handleTna(const std::vector<std::string>& args);
            void handlePnw(const std::vector<std::string>& args);
            void handlePpo(const std::vector<std::string>& args);
            void handlePlv(const std::vector<std::string>& args);
            void handlePin(const std::vector<std::string>& args);
            void handlePex(const std::vector<std::string>& args);
            void handlePbc(const std::vector<std::string>& args);
            void handlePic(const std::vector<std::string>& args);
            void handlePie(const std::vector<std::string>& args);
            void handlePfk(const std::vector<std::string>& args);
            void handlePdr(const std::vector<std::string>& args);
            void handlePgt(const std::vector<std::string>& args);
            void handlePdi(const std::vector<std::string>& args);
            void handleEnw(const std::vector<std::string>& args);

        private:
            int _mapWidth = 0;
            int _mapHeight = 0;
            bool _running = false;
            bool _mapReady = false;
            int _bctNb = 0;
            std::map<std::pair<int, int>, Tile> _tiles;
            std::map<int, std::shared_ptr<Player>> _players;
            std::vector<std::string> _teamNames;
            std::map<std::string, std::function<void(const std::vector<std::string>&)>> _commands;
            std::shared_ptr<sf::TcpSocket> _sock;
            std::shared_ptr<Zappy::Network> _network;
            std::string _readBuffer;
    };
}

#endif /* !PARSESERVER_HPP */
