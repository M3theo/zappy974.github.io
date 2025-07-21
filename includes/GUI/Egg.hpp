/*
** EPITECH PROJECT, 2025
** Egg
** File description:
** Egg
*/

#ifndef EGG_HPP
    #define EGG_HPP

    #include <iostream>
    #include <string.h>
    #include <SFML/Graphics.hpp>
    #include <unistd.h>
    #include <sstream>

namespace Zappy
{
    class Egg
    {
        public:
            //-----------CONSTRUCTOR-----------//
            Egg(int id, int teamId, int x, int y);
            ~Egg() = default;

            //-----------GETTERS-----------//
            int getID(void);
            int getTeamID(void);
            float getTimer(void);

            //-----------LOGIC-----------//
            void update(float deltaTime);

            //-----------RENDERING-----------//
            void draw(sf::RenderWindow &window, float posX, float posY) const;
            sf::FloatRect getBounds(float posX, float posY) const;

        private:
            int id;
            int teamid;
            int x;
            int y;
            float timer;
            bool destroyed;
            sf::Texture _texture;
            sf::Sprite _sprite;
    };
}

#endif /* !EGG_HPP */
