/*
** EPITECH PROJECT, 2025
** egg
** File description:
** egg
*/

#include "Egg.hpp"

Zappy::Egg::Egg(int id, int teamId, int x, int y) : id(id), teamid(teamId), x(x), y(y)
{
    if (!_texture.loadFromFile("./src/GUI/assets/Egg_triso.png")) {
        std::cerr << "Failed to load player texture\n";
    } else {
        _sprite.setTexture(_texture);
        _sprite.setScale(0.05f, 0.05f);
    }
}

void Zappy::Egg::update(float deltaTime)
{
    (void)deltaTime;
}

void Zappy::Egg::draw(sf::RenderWindow &window, float posX, float posY) const
{
    sf::Sprite sprite = _sprite;

    sprite.setPosition(posX, posY);
    window.draw(sprite);
}

sf::FloatRect Zappy::Egg::getBounds(float posX, float posY) const
{
    sf::Sprite spriteCopy = _sprite;
    spriteCopy.setScale(0.05f, 0.05f);
    spriteCopy.setPosition(posX + 2.f, posY + 2.f);

    return spriteCopy.getGlobalBounds();
}

int Zappy::Egg::getID(void)
{
    return this->id;
}

int Zappy::Egg::getTeamID(void)
{
    return this->teamid;
}

float Zappy::Egg::getTimer(void)
{
    return this->timer;
}