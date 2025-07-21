/*
** EPITECH PROJECT, 2025
** map
** File description:
** map
*/

#ifndef MAP_HPP_
    #define MAP_HPP_

    #include <vector>
    #include <SFML/Graphics.hpp>
    #include <memory>
    #include "Tile.hpp"
    #include "Player.hpp"
    #include "ParseServer.hpp"

namespace Zappy
{
    class Map
    {
        public:
            Map(int width, int height, sf::RenderWindow &window, const ParseServer &parseServer);
            void draw(sf::RenderWindow& window) const;
            void checkHoverTile(sf::RenderWindow &window) const;
            void updateTile(int x, int y, const std::map<std::string, int>& resources, std::map<int, std::shared_ptr<Player>> _players);
            const sf::RectangleShape& getShape() const { return shape; };
            std::string getPlayerHoverInfo(const sf::Vector2f& worldPos) const;
            std::string getTileHoverInfo(const sf::Vector2f& worldPos) const;
            std::string getTileAtPosition(int x, int y, const sf::Vector2f& worldPos) const;
            void drawHoverPopup(sf::RenderWindow& window, const std::string& info) const;

        private:
            int _width;
            int _height;
            int _tileSize;
            int _offsetX = 0;
            int _offsetY = 0;
            bool _isDragging;
            float _zoomLevel;
            sf::RectangleShape shape;
            sf::Texture _tileTexture;
            sf::RenderWindow &_window;
            sf::View _mapView;
            sf::Vector2f _dragStartPosition;
            const Zappy::ParseServer& _parseServer;
            std::vector<std::vector<std::shared_ptr<Tile>>> _tiles;
    };
}

#endif /* !MAP_HPP_ */
