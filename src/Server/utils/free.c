/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-julien.kbidi
** File description:
** free
*/

#include "server.h"

void free_all(global_t *global)
{
    if (!global)
        return;
    if (!global->flags->teams_name)
        return;
    for (int i = 0; global->flags->teams_name[i]; i++)
        free(global->flags->teams_name[i]);
    free(global->flags->teams_name);
    close(SERVER->listenfd);
    free(global->flags);
    free(global->world);
    free(SERVER);
    free(global);
}
