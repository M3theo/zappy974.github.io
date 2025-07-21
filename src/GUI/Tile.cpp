/*
** EPITECH PROJECT, 2025
** tile
** File description:
** tile
*/

#include "Tile.hpp"

std::map<std::string, sf::Texture> Zappy::Tile::_resourceTextures;

Zappy::Tile::Tile(int x, int y, int size) : _x(x), _y(y)
{
    shape.setSize(sf::Vector2f(size, size));
    shape.setPosition(0, 0);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(1.f);
    shape.setOutlineColor(sf::Color(80, 80, 80));
    loadResourcesTextures();
}

void Zappy::Tile::loadResourcesTextures()
{
    if (_resourceTextures.empty()) {
        if (!_resourceTextures["food"].loadFromFile("./src/GUI/assets/food.png"))
            std::cerr << "Failed to load food texture" << std::endl;
        if (!_resourceTextures["linemate"].loadFromFile("./src/GUI/assets/green.png"))
            std::cerr << "Failed to load linemate texture" << std::endl;
        if (!_resourceTextures["deraumere"].loadFromFile("./src/GUI/assets/blue.png"))
            std::cerr << "Failed to load deraumere texture" << std::endl;
        if (!_resourceTextures["sibur"].loadFromFile("./src/GUI/assets/black.png"))
            std::cerr << "Failed to load sibur texture" << std::endl;
        if (!_resourceTextures["mendiane"].loadFromFile("./src/GUI/assets/purple.png"))
            std::cerr << "Failed to mendiane food texture" << std::endl;
        if (!_resourceTextures["phiras"].loadFromFile("./src/GUI/assets/pink.png"))
            std::cerr << "Failed to load phiras texture" << std::endl;
        if (!_resourceTextures["thystame"].loadFromFile("./src/GUI/assets/red.png"))
            std::cerr << "Failed to load thystame texture" << std::endl;
        for (auto& [name, texture] : _resourceTextures) {
            sf::Sprite sprite;
            sprite.setTexture(texture);
            _resourceSprites[name] = sprite;
        }
    }
}

void Zappy::Tile::addRessource(const std::string &resource)
{
    if (_resources.count(resource) == 0)
        _resources[resource] = 1;
    else
        _resources[resource] = _resources[resource] + 1;
}

void Zappy::Tile::setPosition(float x, float y)
{
    shape.setPosition(x, y);
}

void Zappy::Tile::removeRessource(const std::string &resource)
{
    std::map<std::string, int>::iterator it;
    for (it = _resources.begin(); it != _resources.end(); it++) {
        if (it->first == resource) {
            if (it->second > 1)
                it->second = it->second - 1;
            else
                _resources.erase(it);
            break;
        }
    }
}

int Zappy::Tile::drawResources(sf::RenderWindow &window) const
{
    const float tileSize = shape.getSize().x;
    const float resSize = tileSize / 4.0f;
    const float spacing = 1.0f;
    const int maxPerLine = static_cast<int>(tileSize / (resSize + spacing));
    int index = 0;
    float baseX = shape.getPosition().x + spacing;
    float baseY = shape.getPosition().y + spacing;

    for (const auto& [name, quantity] : _resources) {
        if (quantity <= 0 || _resourceTextures.find(name) == _resourceTextures.end())
            continue;
        sf::Sprite resourceSprite;
        resourceSprite.setTexture(_resourceTextures.at(name));
        sf::FloatRect spriteSize = resourceSprite.getLocalBounds();
        float scale = resSize / std::max(spriteSize.width, spriteSize.height);
        resourceSprite.setScale(scale, scale);
        int col = index % maxPerLine;
        int row = index / maxPerLine;
        float x = baseX + col * (resSize + spacing);
        float y = baseY + row * (resSize + spacing);
        resourceSprite.setPosition(x, y);
        window.draw(resourceSprite);
        index++;
    }
    return index;
}

std::tuple<bool, std::string, float> Zappy::Tile::hoverPlayer(const sf::Vector2f &mousePos) const
{
    float baseX = shape.getPosition().x;
    float baseY = shape.getPosition().y;

    for (const auto& player : _players) {
        sf::FloatRect bounds = player.second->getBounds(baseX, baseY);
        if (bounds.contains(mousePos))
            return std::make_tuple(true, player.second->getTeamName(), player.second->getLevel());
    }
    return std::make_tuple(false, "", 0.0f);
}

void Zappy::Tile::addEgg(std::shared_ptr<Egg> egg)
{
    _eggs.push_back(egg);
}

void Zappy::Tile::drawEggs(sf::RenderWindow &window) const
{
    const float tileSize = shape.getSize().x;

    for (size_t i = 0; i < _eggs.size(); i++)
        _eggs[i]->draw(window, shape.getPosition().x + tileSize / 2.0f, shape.getPosition().y + 2);
}

void Zappy::Tile::setResources(const std::map<std::string, int>& resources)
{
    _resources = resources;
}

void Zappy::Tile::setIncantation(bool state, int level)
{
    _isIncanting = state;
    _incantationLevel = level;
    if (state)
        std::cout << "Incantation level " << level << " started on this tile" << std::endl;
    else
        std::cout << "Incantation ended on this tile" << std::endl;
}

void Zappy::Tile::addPlayer(std::map<int, std::shared_ptr<Player>> players)
{
    _players = players;
}

std::string Zappy::Tile::getHoverInfo(sf::Vector2f mousePos)
{
    const float tileSize = shape.getSize().x;
    sf::FloatRect bounds(shape.getPosition().x, shape.getPosition().y, tileSize, tileSize);
    std::stringstream ss;

    if (!bounds.contains(mousePos))
        return "";
    if (!_resources.empty()) {
        ss << "Ressources:\n";
        for (auto &r : _resources)
            ss << " - " << r.first << " x" << r.second << "\n";
    }
    return ss.str();
}
