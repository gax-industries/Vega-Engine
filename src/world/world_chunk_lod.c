/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

chunk_lod_t chunk_lod_create(void)
{
    chunk_lod_t res;

    res.tree = octree_create(NULL);
    res.vertex_buffer = 0;
    res.do_reupload_buf = 1;
    return res;
}

void chunk_lod_destroy(chunk_lod_t lod)
{
    octree_destroy(&lod.tree);
    if (lod.vertex_buffer != 0)
        glDeleteBuffers(1, &lod.vertex_buffer);
}

void chunk_load_insert_rtx_triangle(chunk_lod_t *lod, rtx_triangle *triangle)
{
    octree_insert_triangle(&lod->tree, triangle);
    lod->do_reupload_buf = 1;
}
