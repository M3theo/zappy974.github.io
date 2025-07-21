/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-julien.kbidi
** File description:
** take
*/

#include "../../../../includes/Server/server.h"

int get_ressource_id(char *input)
{
    const char *r_names[] = {"food", "linemate", "deraumere",
        "sibur", "mendiane", "phiras", "thystame"};

    for (int i = 0; i < 7; i++) {
        if (strcmp(r_names[i], input) == 0)
            return i;
    }
    return -1;
}

void cmd_take(global_t *global, int client_id, char *args)
{
    player_t *p = get_player_by_client_id(global, client_id);
    char *token = strtok(NULL, "\n\t\r");
    int index = 0;

    (void)args;
    if (!p) {
        dprintf(SERVER->pfds[client_id].fd, "ko\n");
        LOG_WARN("Client ID [%d]: Take failed.", client_id);
        return;
    }
    if (!token) {
        for (int i = 0; i < 7; i++) {
            p->ressources[i] += WORLD->map[p->pos_y][p->pos_x].ressources[i];
            WORLD->map[p->pos_y][p->pos_x].ressources[i] = 0;
        }
    } else {
        index = get_ressource_id(token);
        p->ressources[index] += WORLD->map[p->pos_y][p->pos_x].ressources[index];
        WORLD->map[p->pos_y][p->pos_x].ressources[index] = 0;
    }
    dprintf(SERVER->pfds[client_id].fd, "ok\n");
    send_pgt(global, WORLD->players, SERVER->gui_client, index);
    LOG_INFO("Client [%d]: Take %s at [%d;%d]", client_id,
            token ? token : "all", p->pos_x, p->pos_y);
}
