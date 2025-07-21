/*
** EPITECH PROJECT, 2025
** player
** File description:
** player
*/

#include "Player.hpp"

Zappy::Player::Player(int id, int x, int y, Direction direction, const std::string &team, int mapWidth, int mapHeight) : id(id), _x(x), _y(y), _mapWidth(mapWidth), _mapHeight(mapHeight), _level(1), team(team), lifeUnits(1260), _direction(direction), _currentAction(IDLE)
{
    if (!_directionTextures[SOUTH].loadFromFile("./src/GUI/assets/Trisorien.png")
        || !_directionTextures[EAST].loadFromFile("./src/GUI/assets/Trisorien_profil.png")
        || !_directionTextures[NORTH].loadFromFile("./src/GUI/assets/Trisorien_dos.png"))
        std::cerr << "Failed to load player textures" << std::endl;
    _sprite.setTexture(_directionTextures[direction]);
    _sprite.setScale(0.1f, 0.1f);
    _inventory = {
        {"food", 0},
        {"linemate", 0},
        {"deraumere", 0},
        {"sibur", 0},
        {"mendiane", 0},
        {"phiras", 0},
        {"thystame", 0}
    };
}

void Zappy::Player::draw(sf::RenderWindow &window, float tileSize, float offsetX, float offsetY) const
{
    float posX = _x * tileSize + offsetX;
    float posY = _y * tileSize + offsetY;
    sf::Sprite spriteToDraw = _sprite;

    spriteToDraw.setPosition(posX + tileSize / 2, posY + tileSize/  2);
    spriteToDraw.setOrigin(_sprite.getTexture()->getSize().x / 2,  _sprite.getTexture()->getSize().y / 2);
    spriteToDraw.setRotation(static_cast<float>(_direction));
    window.draw(spriteToDraw);
}

std::string Zappy::Player::getTeamName(void)
{
    return this->team;
}

float Zappy::Player::getLevel(void)
{
    return this->_level;
}

sf::FloatRect Zappy::Player::getBounds(float posX, float posY) const
{
    sf::Sprite spriteCopy = _sprite;
    float width = _sprite.getGlobalBounds().width;
    float height = _sprite.getGlobalBounds().height;

    spriteCopy.setPosition(posX, posY);
    return sf::FloatRect(posX - width/2, posY - height/2, width, height);
}

void Zappy::Player::setInventory(const std::map<std::string, int>& inventory)
{
    this->_inventory = {
        {"food", 0},
        {"linemate", 0},
        {"deraumere", 0},
        {"sibur", 0},
        {"mendiane", 0},
        {"phiras", 0},
        {"thystame", 0}
    };
    for (const auto& [resource, quantity] : inventory) {
        if (this->_inventory.find(resource) != this->_inventory.end())
            this->_inventory[resource] = quantity;
    }
}

void Zappy::Player::setMapSize(int width, int height)
{
    _mapWidth = width;
    _mapHeight = height;
}

void Zappy::Player::updateSpriteTexture()
{
    switch(_direction) {
        case SOUTH:
            _sprite.setTexture(_directionTextures[SOUTH]);
            _sprite.setScale(0.1f, 0.1f);
            break;
        case EAST:
            _sprite.setTexture(_directionTextures[EAST]);
            _sprite.setScale(0.1f, 0.1f);
            break;
        case NORTH:
            _sprite.setTexture(_directionTextures[NORTH]);
            _sprite.setScale(-0.1f, 0.1f);
            break;
        case WEST:
            _sprite.setTexture(_directionTextures[EAST]);
            _sprite.setScale(-0.1f, 0.1f);
            break;
    }
}

std::string Zappy::Player::getHoverInfo() const
{
    std::stringstream ss;

    ss << "Player #" << id << "\n";
    ss << "Team: " << team << "\n";
    ss << "Level: " << _level << "\n";
    ss << "Position: [" << _x << "; " << _y << "]\n";
    ss << "Direction: ";
    switch(_direction) {
        case NORTH: ss << "NORTH";
            break;
        case EAST: ss << "EAST";
            break;
        case SOUTH: ss << "SOUTH";
            break;
        case WEST: ss << "WEST";
            break;
    }
    ss << "\nInventory:\n";
    for (const auto& [item, quantity] : _inventory)
        ss << "  - " << item << ": " << quantity << "\n";
    return ss.str();
}
