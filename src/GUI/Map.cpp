/*
** EPITECH PROJECT, 2025
** map
** File description:
** map
*/

#include "Map.hpp"
#include "Player.hpp"
#include "Egg.hpp"

Zappy::Map::Map(int width, int height, sf::RenderWindow &window, const Zappy::ParseServer &parseServer) : _width(width), _height(height), _window(window), _parseServer(parseServer)
{
    sf::Vector2u windowSize = window.getSize();
    int popupMargin = 400;
    int tileWidth = (windowSize.x - popupMargin) / width;
    int tileHeight = windowSize.y / height;
    std::shared_ptr<Tile> tile;

    if (!_tileTexture.loadFromFile("./src/GUI/assets/tile_triso.png"))
        std::cerr << "Failed to load tile texture" << std::endl;
    _tileSize = std::min(tileWidth, tileHeight);
    _offsetX = 30;
    _offsetY = (windowSize.y - (_tileSize * _height)) / 2;
    _tiles.reserve(height);
    for (int y = 0; y < height; y++) {
        std::vector<std::shared_ptr<Tile>> row;
        row.reserve(width);
        for (int x = 0; x < width; x++) {
            tile = std::make_shared<Tile>(x, y, _tileSize);
            tile->setPosition(x * _tileSize + _offsetX, y * _tileSize + _offsetY);
            row.emplace_back(tile);
        }
        _tiles.push_back(row);
    }
}

void Zappy::Map::draw(sf::RenderWindow &window) const
{
    sf::Sprite tileSprite;
    tileSprite.setTexture(_tileTexture);
    tileSprite.setScale(static_cast<float>(_tileSize) / _tileTexture.getSize().x, static_cast<float>(_tileSize) / _tileTexture.getSize().y);
    int total = 0;

    for (auto row : _tiles) {
        for (auto tile : row) {
            tileSprite.setPosition(tile->getShape().getPosition());
            window.draw(tileSprite);
            window.draw(tile->getShape());
            total += tile->drawResources(window);
            tile->drawEggs(window);
        }
    }
    std::string text = "    INFOMATION   OF   MAP:\n Width: " + std::to_string(_width) + "               Height: " + std::to_string(_height) + "\n     Total Ressources: " + std::to_string(total);
    static sf::Font font;
    font.loadFromFile("./src/GUI/assets/font.ttf");
    sf::RectangleShape popupWindow(sf::Vector2f(350, 100));
    popupWindow.setFillColor(sf::Color(0, 0, 0, 180));
    popupWindow.setOutlineColor(sf::Color::White);
    popupWindow.setOutlineThickness(1);
    popupWindow.setPosition(window.getSize().x - 380, 40);
    sf::Text popup(text, font, 18);
    popup.setFillColor(sf::Color::White);
    popup.setPosition(window.getSize().x - 320, 40);
    popup.setOutlineColor(sf::Color::Black);
    popup.setOutlineThickness(1.f);
    window.draw(popupWindow);
    window.draw(popup);
    for (const auto &[id, player] : _parseServer.getPlayers())
        player->draw(window, _tileSize, _offsetX, _offsetY);
    checkHoverTile(window);
}

void Zappy::Map::updateTile(int x, int y, const std::map<std::string, int> &resources, std::map<int, std::shared_ptr<Player>> _players)
{
    if (x >= 0 && x < _width && y >= 0 && y < _height)
        _tiles[y][x]->setResources(resources);
    else
        std::cerr << "Invalid tile coordinates: (" << x << "," << y << ")" << std::endl;
    for (const auto& [id, player] : _players) {
        if (x >= 0 && x < _width && y >= 0 && y < _height && x == player->getX() && y == player->getY())
        _tiles[y][x]->addPlayer(_players);
    }
}

std::string Zappy::Map::getPlayerHoverInfo(const sf::Vector2f& worldPos) const
{
    for (const auto& [id, player] : _parseServer.getPlayers()) {
        float posX = player->getX() * _tileSize + _offsetX + _tileSize / 2;
        float posY = player->getY() * _tileSize + _offsetY + _tileSize / 2;
        sf::FloatRect bounds = player->getBounds(posX, posY);
        if (bounds.contains(worldPos)) {
            std::string playerInfo = player->getHoverInfo();
            std::string tileInfo = getTileAtPosition(player->getX(), player->getY(), worldPos);
            std::string combined;
            if (!playerInfo.empty())
                combined += "--- PLAYER ---\n" + playerInfo + "\n\n";
            if (!tileInfo.empty())
                combined += "--- TILE ---\n" + tileInfo;
            return combined;
        }
    }
    return "";
}

std::string Zappy::Map::getTileAtPosition(int x, int y, const sf::Vector2f& worldPos) const
{
    if (x >= 0 && x < _width && y >= 0 && y < _height)
        return _tiles[y][x]->getHoverInfo(worldPos);
    return "";
}

std::string Zappy::Map::getTileHoverInfo(const sf::Vector2f& worldPos) const
{
    for (const auto& row : _tiles) {
        for (const auto& tile : row) {
            std::string tileInfo = tile->getHoverInfo(worldPos);
            if (!tileInfo.empty())
                return "--- TILE ---\n" + tileInfo;
        }
    }
    return "";
}

void Zappy::Map::drawHoverPopup(sf::RenderWindow& window, const std::string& info) const
{
    static sf::Font font;
    static bool fontLoaded = false;
    int lineCount = std::count(info.begin(), info.end(), '\n') + 1;
    int popupHeight = 40 + lineCount * 22;

    if (!fontLoaded) {
        font.loadFromFile("./src/GUI/assets/font.ttf");
        fontLoaded = true;
    }
    sf::RectangleShape popupWindow(sf::Vector2f(350, popupHeight));
    popupWindow.setPosition(window.getSize().x - 380, 180);
    popupWindow.setFillColor(sf::Color(0, 0, 0, 180));
    popupWindow.setOutlineColor(sf::Color::White);
    popupWindow.setOutlineThickness(1);
    sf::Text popupText(info, font, 18);
    popupText.setFillColor(sf::Color::White);
    popupText.setOutlineColor(sf::Color::Black);
    popupText.setOutlineThickness(0.5f);
    popupText.setPosition(window.getSize().x - 370, 190);
    window.draw(popupWindow);
    window.draw(popupText);
}

void Zappy::Map::checkHoverTile(sf::RenderWindow& window) const
{
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
    std::string hoverInfo = getPlayerHoverInfo(worldPos);

    if (hoverInfo.empty())
        hoverInfo = getTileHoverInfo(worldPos);
    if (!hoverInfo.empty())
        drawHoverPopup(window, hoverInfo);
}
