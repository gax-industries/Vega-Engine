/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** quest_sys
*/

#include "headers.h"

void main_quest_start(void)
{
    _iu.current_dialogue =
    _demo->quest.quest[_demo->quest.curr_main_quest].first_dial;
}