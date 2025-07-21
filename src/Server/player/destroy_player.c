/*
** EPITECH PROJECT, 2025
** Destroy_player.c
** File description:
** Zappy
*/

#include "../../../includes/Server/server.h"

void disconnect_client(global_t *global, int i, int *nfds)
{
    int fd = SERVER->pfds[i].fd;
    player_t *prev = NULL;
    player_t *curr = WORLD->players;
    int player_id = SERVER->clients[i] ? SERVER->clients[i]->id : -1;

    if (SERVER->gui_client == i)
        SERVER->gui_client = 0;
    else
        send_pdi(global, WORLD->players, SERVER->gui_client);
    LOG_INFO("Client ID [%d] disconnected.", i);
    close(fd);
    while (curr) {
        if ((int)curr->id == player_id) {
            if (prev)
                prev->next = curr->next;
            else
                WORLD->players = curr->next;
            LOG_DEBUG("Deleted player ID=%d from world", player_id);
            free(curr->team_name);
            free(curr);
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    if (SERVER->clients[i]) {
        free(SERVER->clients[i]);
        SERVER->clients[i] = NULL;
    }
    SERVER->pfds[i] = SERVER->pfds[*nfds - 1];
    SERVER->clients[i] = SERVER->clients[*nfds - 1];
    SERVER->pfds[*nfds - 1].fd = -1;
    SERVER->pfds[*nfds - 1].events = 0;
    SERVER->clients[*nfds - 1] = NULL;
    (*nfds)--;
}
