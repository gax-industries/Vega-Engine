/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** ui_lightmap_draw
*/

#include "headers.h"

void ui_lightmap_draw(display_nbr_array_t nbr_array)
{
    for (int i = 0; i < UILMBUTTON_END; i++) {
        button_draw(_ui.ui_lightmap_struct.object[i]);
    }
    for (int i = 0; i < nbr_array.nb_digit; i++)
        button_draw(nbr_array.digits[i].digit);
}