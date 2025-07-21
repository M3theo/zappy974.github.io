/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-julien.kbidi
** File description:
** connexion
*/

#include "../../../includes/Server/server.h"

int accept_connexion(global_t *global, int *nfds)
{
    int connfd = accept(SERVER->listenfd, NULL, NULL);

    if (connfd < 0) {
        perror("accept");
        return -1;
    }
    for (int i = 1; i < MAX_CLIENT_INDEX; i++) {
        if (SERVER->pfds[i].fd == -1) {
            SERVER->pfds[i].fd = connfd;
            SERVER->pfds[i].events = POLLIN;
            SERVER->pfds[i].revents = 0;
            SERVER->clients[i] = init_client(i);
            if (i >= *nfds)
                *nfds = i + 1;
            write(connfd, "WELCOME\n", 8);
            return connfd;
        }
    }
    close(connfd);
    return -1;
}

void poll_connexion(global_t *global, int *nfds)
{
    if (poll(SERVER->pfds, *nfds, 0) < 0) {
        perror("poll");
        return;
    }
    if (SERVER->pfds[0].revents & POLLIN)
        accept_connexion(global, nfds);
    for (int i = 1; i < *nfds; i++) {
        if (SERVER->pfds[i].fd == -1)
            continue;
        if (SERVER->pfds[i].revents & (POLLIN | POLLHUP | POLLERR)) {
            if (!handle_client_data(global, i))
                disconnect_client(global, i, nfds);
        }
    }
}
