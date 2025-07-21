/*
** EPITECH PROJECT, 2025
** handle_commands.c
** File description:
** Zappy
*/

#include "server.h"

void send_tna(global_t *global, UI index)
{
    if (!index)
        return;
    for (int i = 0; FLAGS->teams_name[i]; i++)
        dprintf(SERVER->pfds[index].fd, "tna %s\n", FLAGS->teams_name[i]);
}

void send_pex(global_t *global, player_t *player, UI index)
{
    if (!index)
        return;
    dprintf(SERVER->pfds[index].fd, "pex #%d\n", player->id);
}

void send_pbc(global_t *global, player_t *player, UI index, const char *msg)
{
    if (!index)
        return;
    dprintf(SERVER->pfds[index].fd, "pbc #%d %s\n", player->id, msg);
}

// void send_pic(global_t *global, player_t *player, UI index)
// {
//     dprintf(SERVER->pfds[index].fd, "pic #%d %s ...\n",
//         player->pos_x,
//         player->pos_y,
//         player->id);
// }

// void send_pie(global_t *global, UI index)
// {}

void send_pfk(global_t *global, player_t *player, UI index)
{
    if (!index)
        return;
    dprintf(SERVER->pfds[index].fd, "pfk #%d\n", player->id);
}

void send_pdr(global_t *global, player_t *player, UI index, int res_idx)
{
    if (!index)
        return;
    dprintf(SERVER->pfds[index].fd, "pdr #%d %d\n",
        player->id,
        player->ressources[res_idx]);
}

void send_pgt(global_t *global, player_t *player, UI index, int res_idx)
{
    if (!index)
        return;
    dprintf(SERVER->pfds[index].fd, "pgt #%d %d\n",
        player->id,
        player->ressources[res_idx]);
}

void send_pdi(global_t *global, player_t *player, UI index)
{
    if (!index)
        return;
    dprintf(SERVER->pfds[index].fd, "pdi #%d\n", player->id);
}

// Raphaël à pas encore
// void send_enw(global_t *global, player_t *player, UI index)
// {}

// void send_ebo(global_t *global, UI index)
// {}

// void send_edi(global_t *global, UI index)
// {}

// void send_sgt(global_t *global, UI index)
// {}

// void send_sst(global_t *global, UI index)
// {}

void send_seg(global_t *global, team_t *team, UI index)
{
    if (!index)
        return;
    dprintf(SERVER->pfds[index].fd, "seg %s\n", team->team_name);
}

void send_smg(global_t *global, UI index, const char *msg)
{
    if (!index)
        return;
    dprintf(SERVER->pfds[index].fd, "smg %s\n", msg);
}

void send_suc(global_t *global, UI index)
{
    if (!index)
        return;
    dprintf(SERVER->pfds[index].fd, "suc\n");
}

void send_sbp(global_t *global, UI index)
{
    if (!index)
        return;
    dprintf(SERVER->pfds[index].fd, "sbp\n");
}
