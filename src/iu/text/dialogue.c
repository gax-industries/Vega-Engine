/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** dialogue
*/

#include "headers.h"

const text_src_t text_array[] = {
    {TEXT_TEST, "Welcome in the Vega World ! Here the world is a bit strange"},
    {TEXT_TEST_1, "You can't fight, you cant leave you're cuck ! GLHF to understand the equations behind these world"},
    {TEXT_TEST_2, "Do you want to kys ?"},
    {TEXT_MAIN1_START1, "Hey you're new here, meh actualy you're also the first visitor I've seen in a while"},
    {TEXT_MAIN1_START2, "I don't know why nobody want to live here, anyways you're here and you'll never leave this place"},
    {TEXT_MAIN1_START3, "You know what let's fill the time I give you a job !"},
    {TEXT_MAIN1_SCHOICE, "Farm to level 5 ok ? and come back !"},
    {TEXT_MAIN2_START1, "Congratulation I hope it wasn't to long, anyway I have another job for you"},
    {TEXT_MAIN2_START2, "For the next steps of our aventure you will need some planks ! Yeah 50 planks. What ? Dispapointed ?"},
    {TEXT_MAIN2_START3, "I don't care get me this planks ! You've nothing better to do anyways. Try to kill these strange moving house to get planks"},
    {TEXT_MAIN3_START1, "You got the Planks ! Perfect ! you deserved the sword you just received. And you'll need here for the next task"},
    {TEXT_MAIN3_START2, "There is s starnge creature in my beautifull world And i want here to die ! And you'll do it for me !"},
    {TEXT_MAIN3_START3, "To summons her you should kill fish she'll be very angry eheh"},
    {TEXT_MAINBOSS, "ITS HIM THE DOOMED FISH KILL HIM NOOOOW !!!"},
    {TEXT_END_1, "You did it !! The simpliest task ever seen congratulation !"},
    {TEXT_END_2, "Now I didn't see any reasons to let you here"},
    {TEXT_END_CHOICE, "Do you want to stay a bit ?"},
    {TEXT_INVENT_FULL, "Inventory Full !!"},
    {TEXT_WARNING_SCREEN, "Modifications will be applied once returned in the game"},
    {0, NULL}
};

void iu_text_init(void)
{
    for (int i = 0; i < TEXT_END; i++)
        _iu.text_src[i] = NULL;
    for (int i = 0; text_array[i].src != NULL; i++)
        _iu.text_src[text_array[i].index] =
        text_array[i].src;
    _iu.current_dialogue = DIALOGUE_END;
}

void iu_set_dialogue(void)
{
    _iu.dialogue_list[DIALOGUE_WELCOME] = vg_dialogue_create(3, TEXT_TEST);
    vg_dialogue_set_position(&_iu.dialogue_list[DIALOGUE_WELCOME],
    (vec2){-0.45f, -0.80f});
    vg_dialogue_set_choices(&_iu.dialogue_list[DIALOGUE_WELCOME],
    "(A) : Acepter", "(E) : Refuser", &vg_effect_quit, &vg_no_effect);
}
