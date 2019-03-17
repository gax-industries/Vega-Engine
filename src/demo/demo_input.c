/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static void poll_editor(demo_t *demo, vec3 cam_x, vec3 cam_z)
{
    if (sfKeyboard_isKeyPressed(sfKeyZ))
        demo->cam.pos =
        vec3_add(demo->cam.pos, vec3_muls(cam_z, CAM_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeyS))
        demo->cam.pos =
        vec3_sub(demo->cam.pos, vec3_muls(cam_z, CAM_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeyD))
        demo->cam.pos =
        vec3_add(demo->cam.pos, vec3_muls(cam_x, CAM_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeyQ))
        demo->cam.pos =
        vec3_sub(demo->cam.pos, vec3_muls(cam_x, CAM_MOVE));
}

static void poll_playing(demo_t *demo, vec3 cam_x, vec3 cam_z)
{
    cam_z.y = 0.0;
    if (sfKeyboard_isKeyPressed(sfKeyZ))
        demo->player.speed =
        vec3_add(demo->player.speed, vec3_muls(cam_z, PLAYER_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeyS))
        demo->player.speed =
        vec3_sub(demo->player.speed, vec3_muls(cam_z, PLAYER_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeyD))
        demo->player.speed =
        vec3_add(demo->player.speed, vec3_muls(cam_x, PLAYER_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeyQ))
        demo->player.speed =
        vec3_sub(demo->player.speed, vec3_muls(cam_x, PLAYER_MOVE));
    if (sfKeyboard_isKeyPressed(sfKeySpace) && demo->player.is_grounded)
        demo->player.speed.y = 3.0f;
    player_physics(demo);
}

static void poll_general(demo_t *demo)
{
    for (size_t i = 0; i < 256; i++)
        demo->input.key_last[i] = demo->input.key_state[i];
    for (size_t i = 0; i < 26; i++)
        demo->input.key_state['A' + i] = sfKeyboard_isKeyPressed(sfKeyA + i);
    demo->input.key_state[KEY_DEL] = sfKeyboard_isKeyPressed(sfKeyDelete);
    for (size_t i = 0; i < 256; i++)
        demo->input.key_press[i] =
        (!demo->input.key_last[i]) && demo->input.key_state[i];
}

void demo_poll_input(demo_t *demo)
{
    vec3 cam_x = spherical_to_cartesian_z_to_x(demo->cam.rot);
    vec3 cam_z = spherical_to_cartesian_z(demo->cam.rot);

    demo_update_framerate(demo);
    cam_x = vec3_muls(cam_x, demo->win.framelen);
    cam_z = vec3_muls(cam_z, demo->win.framelen);
    if (demo->player.state == GAME_EDITOR)
        poll_editor(demo, cam_x, cam_z);
    else
        poll_playing(demo, cam_x, cam_z);
    poll_general(demo);
}
