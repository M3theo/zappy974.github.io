/*
** EPITECH PROJECT, 2025
** player
** File description:
** Player class declaration
*/

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_

    #include <iostream>
    #include <sstream>
    #include <string>
    #include <map>
    #include <array>
    #include <SFML/Graphics.hpp>

namespace Zappy
{
    enum Direction {
        NORTH = 1,
        EAST = 2,
        SOUTH = 3,
        WEST = 4
    };

    enum Action {
        IDLE,
        MOVING,
        INCANTING,
        EJECTING,
        BROADCASTING
    };

    class Player
    {
        public:
            //-----------CONSTRUCTOR-----------//
            Player(int id, int x, int y, Direction direction, const std::string &team, int mapWidth, int mapHeight);
            ~Player() = default;

            //-----------POSITION-----------//
            inline void setPosition(int x, int y) { this->_x = x; this->_y = y; }
            inline int getX() const { return _x; }
            inline int getY() const { return _y; }

            //-----------LEVEL-----------//
            inline void setLevel(int level) { _level = level; }
            inline int getLevel() const { return _level; }

            //-----------DIRECTION-----------//
            inline Direction getDirection() const { return _direction; }
            inline void setDirection(Direction dir) { _direction = dir; _sprite.setRotation(static_cast<float>(dir) * 90.f); }

            //-----------MAP-----------//
            void setMapSize(int width, int height);

            //-----------INVENTORY-----------//
            void setInventory(const std::map<std::string, int>& inventory);
            inline const std::map<std::string, int>& getInventory() {return _inventory; }

            //-----------INFORMATIONS-----------//
            std::string getTeamName(void);
            float getLevel(void);
            sf::FloatRect getBounds(float posX, float posY) const;
            std::string getHoverInfo() const;

            //-----------RENDER-----------//
            void draw(sf::RenderWindow &window, float tileSize, float offsetX, float offsetY) const;
            void updateSpriteTexture();

        private:
            int id;
            int _x;
            int _y;
            int _mapWidth;
            int _mapHeight;
            int _level;
            std::string team;
            int lifeUnits;
            std::map<std::string, int> _inventory;
            Direction _direction;
            Action _currentAction;
            std::array<sf::Texture, 4> _directionTextures;
            sf::Sprite _sprite;
            float _tileSize = 32.f;
    };
}

#endif /* !PLAYER_HPP_ */
