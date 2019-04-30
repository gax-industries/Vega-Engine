/*
** EPITECH PROJECT, 2019
** MUL_my_world_2018
** File description:
** iu_entities
*/

#include "headers.h"

void set_entities(void)
{
    /*_iu.buttons[IUBUTTON_ELON] =
    (entity2_t){IUTEX_ELON, (rect_t){{-0.30f, 0.0f}, {0.1f, 0.1f}},
    -1.0f, IUREL_FULL};*/
    entity_constructor(&_iu.invent_bg[IUINVENT_BG], (entity2_param_t){
    IUTEX_INVENT_BG, (rect_t){{-1.0f, -1.0f},{2.0f, 2.0f}}, -0.997});
    entity_constructor(&_iu.cadre[IUCADRE_BLACK], (entity2_param_t){
    IUTEX_TEXT_CADRE, (rect_t){{-0.5f, -1.0f},{1.0f, 0.3f}}, -0.998});
    entity_constructor(&_iu.invent.item_image, (entity2_param_t){
    IUTEX_ITEM_VOID, (rect_t){{-0.125f, -0.06f},{0.141f, 0.236f}}, -0.998});
    entity_constructor(&_iu.invent.cursor, (entity2_param_t){
    IUTEX_MENU_CURSOR, (rect_t){{-0.15f, -0.25f}, {0.03f, 0.04f}}, -0.998});
    entity_constructor(&_iu.invent.buttons[INVENT_BUTTON_EQUIP],
    (entity2_param_t){IUTEX_INVENT_EQUIP,
    (rect_t){{-0.15f, 0.33f}, {0.3f, 0.3f}}, -0.998});
}