/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** ui_lightmap
*/

#include "headers.h"

void ui_lightmap_set_buttons(void)
{
    _ui.ui_lightmap_struct.object[UILMBUTTON_TITLE] =
    (button_t){UIRES_LM_TITLE, (vec2){-0.30f, 0.40f}, 0.6f, -1.0f, BUTTON_REL_X};
    _ui.ui_lightmap_struct.object[UILMBUTTON_PLUS] =
    (button_t){UIRES_LM_PLUS, (vec2){0.30f, 0.0f}, 0.1f, -1.0f, BUTTON_REL_X};
    _ui.ui_lightmap_struct.object[UILMBUTTON_MINUS] =
    (button_t){UIRES_LM_MINUS, (vec2){-0.40f, 0.0f}, 0.1f, -1.0f, BUTTON_REL_X};
    _ui.ui_lightmap_struct.object[UILMBUTTON_LEGEND] =
    (button_t){UIRES_LM_LEGEND, (vec2){-0.15f, 0.20f}, 0.3f, -1.0f, BUTTON_REL_X};
    _ui.ui_lightmap_struct.object[UILMBUTTON_START] =
    (button_t){UIRES_LM_START, (vec2){-0.20f, -0.45f}, 0.4f, -1.0f, BUTTON_REL_X};
    _ui.ui_lightmap_struct.object[UILMBUTTON_BACK] =
    (button_t){UIRES_LM_BACK, (vec2){0.85f, -0.90f}, 0.1f, -1.0f, BUTTON_REL_X};
    _ui.ui_lightmap_struct.object[UILMBUTTON_ABORT] =
    (button_t){UIRES_LM_ABORT, (vec2){-0.20f, -0.70f}, 0.4f, -1.0f, BUTTON_REL_X};
    _ui.ui_lightmap_struct.object[UILMBUTTON_CADRE] =
    (button_t){UIRES_CADRE, (vec2){-0.50f, 0.0f}, 0.1f, -1.0f, BUTTON_REL_X};
    _ui.ui_lightmap_struct.object[UILMBUTTON_LOADING] =
    (button_t){UIRES_RED, (vec2){-0.42f, 0.0f}, 0.1f, -0.999f, BUTTON_REL_X};
    _ui.ui_lightmap_struct.object[UILMBUTTON_POURCENT] =
    (button_t){UIRES_POURCENT, (vec2){0.12f, 0.20f}, 0.1f, -1.0f, BUTTON_REL_X};
}

void ui_lightmap_display(demo_t *demo)
{
    _ui.ui_lightmap_struct.back = 0;

    while (ui_lm_poll_events(demo) && !_ui.ui_lightmap_struct.back) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(_ui.ui_program);
        refresh_display_nbr_array(_ui.display_nbr_array, demo->temp_ray_density);
        ui_lightmap_draw();
        sfRenderWindow_display(demo->win.window);
    }
}
