/*
** EPITECH PROJECT, 2019
** MUL_my_world_2018
** File description:
** dungeons
*/

#ifndef DUNGEONS_H_
    #define DUNGEONS_H_

#define DUGEONS_ALLOC   3
void dungeons_gen_init(demo_t *demo);

void dungeons_render(demo_t *demo);
void dungeons_gen_all(demo_t *demo, size_t rooms_limit);
#endif /* !DUNGEONS_H_ */
