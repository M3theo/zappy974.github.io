/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-julien.kbidi
** File description:
** gui
*/

#ifndef GUI_HPP_
    #define GUI_HPP_

    #include <iostream>
    #include <string.h>
    #include <SFML/Graphics.hpp>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <sstream>
    #include <thread>
    #include <memory>
    #include <SFML/Network.hpp>
    #include "Map.hpp"
    #include "Player.hpp"
    #include "Egg.hpp"
    #include "Network.hpp"
    #include <iomanip>

namespace Zappy
{
    class GUI
    {
        public:
            //-----------CONSTRUCTOR-----------//
            GUI();
            ~GUI() = default;

            //-----------MAIN LOOP-----------//
            void run(int port);
            void run_server(int port);
            void run_game();
            void render();
            void processEvents();

            //-----------COMMUNICATION-----------//
            bool sendMessage(const std::string& message);

        private:
            std::shared_ptr<sf::TcpSocket> _sock;
            std::shared_ptr<Network> _network;
            bool _connected = false;
            int _mapWidth = 10;
            int _mapHeight = 10;
            std::unique_ptr<Map> _map;
            std::unique_ptr<ParseServer> _parser;
            std::thread _parserThread;
            bool _running;
            sf::RenderWindow _window;
            sf::Texture _backgroundTexture;
            sf::Sprite _backgroundSprite;
            sf::Font _font;
            sf::Text _timerText;
            sf::Clock _gameClock;
    };
}

#endif /* !GUI_HPP_ */
