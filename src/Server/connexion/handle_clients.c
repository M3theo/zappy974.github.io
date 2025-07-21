/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-julien.kbidi
** File description:
** handle_clients
*/

#include "../../../includes/Server/server.h"

void broadcast_to_other_clients(global_t *global, const char *buff, int len,
    int sender_index)
{
    char index_msg[32];
    int sender_fd = SERVER->pfds[sender_index].fd;
    int fd = -1;

    snprintf(index_msg, sizeof(index_msg), "Index: %d\n", sender_index);
    write(sender_fd, index_msg, strlen(index_msg));
    for (int j = 1; j <= MAX_CLIENTS; j++) {
        fd = SERVER->pfds[j].fd;
        if (j != sender_index && fd != -1)
            write(fd, buff, len);
    }
}

static bool read_client_input(global_t *global, int i, char *buffer)
{
    ssize_t bytes = read(SERVER->pfds[i].fd, buffer, 1023);

    if (bytes <= 0)
        return false;
    buffer[bytes] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0';
    return true;
}

bool handle_client_data(global_t *global, int i)
{
    char buffer[1024] = {0};

    if (!read_client_input(global, i, buffer))
        return false;
    if (SERVER->clients[i]->type == CLIENT_UNKNOW) {
        assign_team(global, buffer, i);
        return true;
    }
    LOG_INFO("Client [%d]: %s", i, buffer);
    // broadcast_to_other_clients(global, buffer, strlen(buffer), i);
    handle_ia_command(global, i, buffer);
    return true;
}
