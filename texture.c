/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** nvidia fanboyisme
*/

#include "headers.h"

texture2* texture2_create(uint32_t w, uint32_t h)
{
    texture2 *res = (texture2*)malloc_safe(sizeof(texture2));

    res->w = w;
    res->h = h;
    res->max_ndx = res->w * res->h;
    res->pixel = (uint32_t*)malloc_safe(w * h * sizeof(uint32_t));
    return res;
}

void texture2_destroy(texture2 *texture)
{
    free(texture->pixel);
    free(texture);
}

texture2_binding texture2_binding_create(vec3 *triangle)
{
    texture2_binding res;
    vec2 min;
    vec2 max;
    vec2 dim;

    res.uv[0] = (vec2){0.0f, 0.0f};
    res.uv[1] = (vec2){vec3_dist(triangle[0], triangle[1]), 0.0f};
    res.uv[2] = circle_intersect(
    (circle){res.uv[0], vec3_dist(triangle[0], triangle[2])},
    (circle){res.uv[1], vec3_dist(triangle[1], triangle[2])});
    min = vec2_min(vec2_min(res.uv[0], res.uv[1]), res.uv[2]);
    max = vec2_max(vec2_max(res.uv[0], res.uv[1]), res.uv[2]);
    dim = vec2_sub(max, min);
    dim.x *= 8.0f;
    dim.y *= 8.0f;
    res.texture = texture2_create((uint32_t)dim.x + 1, (uint32_t)dim.y + 1);
    for (size_t i = 0; i < 3; i++)
        res.uv[i] = vec2_sub(res.uv[i], min);
    res.is_linked = 1;
    return res;
}

void texture2_binding_destroy(texture2_binding binding)
{
    if (binding.is_linked)
        texture2_destroy(binding.texture);
}
