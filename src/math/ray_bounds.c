/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** optiiiiiii rtx
*/

#include "headers.h"

/* this code checks whether a 3D ray will go or not trough a cube.      */
/* it does use 1D rays to check that, so i guess it could be used for   */
/* any dimension rays / boundaries                                      */

static int ray1d_bound_inside(ray1 r, float min, float max, vec2 *t)
{
    if (r.v < 0.0f) {
        t->x = MAX(t->x, (max - r.p) / r.v);
        t->y = MIN(t->y, (min - r.p) / r.v);
    } else {
        t->x = MAX(t->x, (min - r.p) / r.v);
        t->y = MIN(t->y, (max - r.p) / r.v);
    }
    return 1;
}

static int ray1d_bound(ray1 r, float min, float max, vec2 *t)
{
    if (r.v == 0.0f)
        return ((r.p >= min) && (r.p < max));
    if (r.p < min) {
        t->x = MAX(t->x, (min - r.p) / r.v);
        t->y = MIN(t->y, (max - r.p) / r.v);
        return (r.v > 0.0f);
    } else if (r.p >= max) {
        t->x = MAX(t->x, (max - r.p) / r.v);
        t->y = MIN(t->y, (min - r.p) / r.v);
        return (r.v < 0.0f);
    } else
        return ray1d_bound_inside(r, min, max, t);
}

int is_ray_in_bounds(ray3 ray, bounds3 bounds)
{
    vec2 t = {-FLT_INF, FLT_INF};

    for (size_t i = 0; i < 3; i++) {
        if (!ray1d_bound((ray1){((float*)&ray.p)[i], ((float*)&ray.v)[i]},
        ((float*)&bounds.min)[i], ((float*)&bounds.max)[i], &t))
            return 0;
    }
    return (t.x <= t.y);
}


int is_ray_in_bounds_seg(ray3 ray, bounds3 bounds)
{
    vec2 t = {-FLT_INF, FLT_INF};

    for (size_t i = 0; i < 3; i++) {
        if (!ray1d_bound((ray1){((float*)&ray.p)[i], ((float*)&ray.v)[i]},
        ((float*)&bounds.min)[i], ((float*)&bounds.max)[i], &t))
            return 0;
    }
    return ((t.x <= t.y) && (t.y >= 0.0f) && (t.x <= 1.0f));
}
