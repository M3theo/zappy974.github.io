/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-julien.kbidi
** File description:
** spawn_resources
*/

#include "server.h"

void spawn_resources(world_t *world, UI height, UI width)
{
    UI x = 0;
    UI y = 0;
    UI res_count[NB_RESSOURCES] = {
        world->food_density,
        world->linemate_density,
        world->deraumere_density,
        world->sibur_density,
        world->mendiane_density,
        world->phiras_density,
        world->thystame_density
    };

    for (int i = 0; i < NB_RESSOURCES; i++) {
        for (UI j = 0; j < res_count[i]; j++) {
            y = rand() % height;
            x = rand() % width;
            world->map[y][x].ressources[i]++;
        }
    }
}
