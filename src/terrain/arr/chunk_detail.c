/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

static arr2d_dvec3_t split(chunk_t *chunk, arr2d_dvec3_t *arr,
chunk_border_t border)
{
    dvec3 chunk_rel = dvec3_init(0.0, 0.0, 0.0);
    arr2d_dvec3_t n;

    for (size_t i = 0; i < CHUNK_GEN_EXT_ITER; i++) {
        terrain_split(arr, 0.05 / (i + 1));
        terrain_apply_constraints(*arr, border, i);
        terrain_send_iter_to_chunk_border(chunk, *arr, i);
    }
    n = terrain_gen_normals(*arr);
    terrain_send_ter_to_chunk_lod_gen(chunk, WORLD_LOD_MAX,
    (terrain_send_ter_arg){*arr, n,
    (srect){{0, 0}, {arr->w, arr->h}}}, chunk_rel);
    return n;
}

static int arr2d_dvec3_is_coord_valid(arr2d_dvec3_t arr, ssize2 uv)
{
    return (uv.x >= 0) && (uv.x < (ssize_t)arr.w) &&
    (uv.y >= 0) && (uv.y < (ssize_t)arr.h);
}

static dvec3 arr2d_dvec3_sample(arr2d_dvec3_t arr, ssize2 uv)
{
    if (arr2d_dvec3_is_coord_valid(arr, uv))
        return arr.dvec3[uv.y * arr.w + uv.x];
    else
        return dvec3_init(0.0, 0.0, 0.0);
}

static dvec3 arr2d_dvec3_sample_linear(arr2d_dvec3_t arr, vec2 uv)
{
    vec2 uv_af = {(arr.w - 1) * uv.x, (arr.h - 1) * uv.y};
    ssize2 uv_a = {uv_af.x, uv_af.y};
    vec2 off = {uv_af.x - uv_a.x, uv_af.y - uv_a.y};
    double c = arr2d_dvec3_is_coord_valid(arr, uv_a) +
    arr2d_dvec3_is_coord_valid(arr, ssize2_add(uv_a, (ssize2){1, 0})) +
    arr2d_dvec3_is_coord_valid(arr, ssize2_add(uv_a, (ssize2){0, 1})) +
    arr2d_dvec3_is_coord_valid(arr, ssize2_add(uv_a, (ssize2){1, 1}));
    dvec3 p[4];

    if (c != 4)
        return arr2d_dvec3_sample(arr, uv_a);
    p[0] = arr2d_dvec3_sample(arr, uv_a);
    p[1] = arr2d_dvec3_sample(arr, ssize2_add(uv_a, (ssize2){1, 0}));
    p[2] = arr2d_dvec3_sample(arr, ssize2_add(uv_a, (ssize2){0, 1}));
    p[3] = arr2d_dvec3_sample(arr, ssize2_add(uv_a, (ssize2){1, 1}));
    return dvec3_interpolate(
    dvec3_interpolate(p[0], p[2], off.y), dvec3_interpolate(p[1], p[3], off.y),
    off.x);
}

static void add_grass(chunk_t *chunk, arr2d_dvec3_t arr, arr2d_dvec3_t n)
{
    entity3 *ent = chunk_add_entity_ext(chunk);
    entity3 *cur;
    entity3 *sub;
    dvec3 off = dvec3_init(CHUNK_SIZE * 0.5, 0.0, CHUNK_SIZE * 0.5);
    double base_sub = CHUNK_SIZE / 16.0;
    dvec3 off2 = dvec3_init(CHUNK_SIZE / 16.0 * 0.5, 0.0,
    CHUNK_SIZE / 16.0 * 0.5);

    ent->trans.pos = off;
    ent->lod_dist = RENDER_OBJ_LOD_DIST_GRASS_CLUSTER1;
    ent->render_is_rec = 1;
    entity3_trans_update(ent);
    for (size_t i = 0; i < 16; i++)
        for (size_t j = 0; j < 16; j++) {
            cur = entity3_create(ent);
            cur->trans.pos = dvec3_sub(dvec3_add(
            dvec3_init(base_sub * j, 0.0, base_sub * i), off2), ent->trans.pos);
            cur->lod_dist = RENDER_OBJ_LOD_DIST_GRASS_CLUSTER2;
            cur->render_is_rec = 1;
            entity3_trans_update(cur);
        }
    for (size_t i = 0; i < 2048 * 16; i++) {
        vec2 uv = {randf(), randf()};
        dvec3 p = arr2d_dvec3_sample_linear(arr, uv);
        dvec3 norm = arr2d_dvec3_sample_linear(n, uv);
        if ((p.y < -40.0) || (norm.y < 0.8) || 
        (arr2d_dvec3_sample_linear(n,
        vec2_add(uv, (vec2){0.01f, 0.01f})).y < 0.8) ||
        (arr2d_dvec3_sample_linear(n,
        vec2_add(uv, (vec2){-0.01f, -0.01f})).y < 0.8))
            continue;
        sub = ent->sub.ent[MIN((size_t)(uv.y * 16), 15) * 16 + MIN((size_t)(uv.x * 16), 15)];
        cur = entity3_create(sub);
        cur->trans.pos = dvec3_sub(dvec3_sub(p, sub->trans.pos), off);
        cur->trans.pos.y -= fabs(norm.y) / 2.0;
        cur->trans.rot.y = randf() * M_PI;
        entity3_set_render(cur, 2,
        mesh_full_ref_bank_init(MESH_BANK_GRASS1), MATERIAL_VEG_GRASS1);
        entity3_trans_update(cur);
    }
}

static int is_pos_valid(dvec3 pos)
{
    return (pos.x > 0.1 * CHUNK_SIZE) && (pos.y < 0.9 * CHUNK_SIZE) &&
    (pos.z > 0.1 * CHUNK_SIZE) && (pos.z < 0.9 * CHUNK_SIZE) && (pos.y > -40.0);
}

static void add_chalet(chunk_t *chunk, dvec3 p, dvec3 norm)
{
    entity3 *ent;

    (void)norm;
    if (!is_pos_valid(p))
        return;
    ent = chunk_add_entity(chunk);
    ent->trans.pos = p;
    ent->trans.rot.y = randf() * M_PI;
    entity3_set_render(ent, 1, mesh_full_ref_bank_init(MESH_BANK_CASA_L1),
    MATERIAL_WOOD);
    ent->trans.scale = dvec3_init(0.1, 0.1, 0.1);
    entity3_bind_col(ent,
    entity3_get_lod_ref(ent, MESH_FULL_REF_RENDER_LOD1));
    ent->lod_dist = RENDER_OBJ_LOD_DIST_FAR;
    entity3_trans_update(ent);
}

static void add_npc(chunk_t *chunk, dvec3 p)
{
    entity3 *ent;
    entity3_tag_enemy_data_t *data;

    if (!is_pos_valid(p))
        return;
    ent = world_add_entity();
    ent->trans.is_physics = 1;
    ent->trans.is_static = 0;
    ent->trans.is_collision = 1;
    ent->trans.slide_threshold = 0.85;
    ent->trans.pos = dvec3_add(p, chunk->ents->trans.pos);
    ent->trans.pos.y += 0.1;
    ent->trans.speed = dvec3_init(0.0, -10.0, 0.0);
    entity3_set_tag(ent, ENTITY3_TAG_ENEMY);
    data = ent->tag_data;
    data->chunk = chunk->pos;
    data->max_speed = 2.0 + randf() * 2.0;
    data->a_vel = 2.0 + randf() * 4.0;
    entity3_trans_update(ent);
    data->spawn = ent->trans.pos;
    entity3_add_trigger(ent, trigger_create(dvec3_init(-1.0, 0.0, -1.0),
    dvec3_init(1.0, 1.0, 1.0), TRIGGER_ON_HIT_NONE));
    entity3_trans_update(ent);
    ent = entity3_create(ent);
    entity3_set_render(ent, 0, mesh_full_ref_bank_init(MESH_BANK_KNIGHT),
    MATERIAL_WOOD);
    ent->trans.scale = dvec3_init(12.0, 12.0, 12.0);
    ent->trans.rot = dvec3_init(0.0, -M_PI / 2.0, 0.0);
    ent->trans.pos = dvec3_init(0.0, 1.0, 0.0);
    entity3_trans_update(ent);
    ent->trans.is_static = 0;
    ent->lod_dist = RENDER_OBJ_LOD_DIST_FAR;
    data->atk = chunk_get_strength(chunk->pos) * 30.0;
    data->is_npc = 1;
}

static void add_vill_ent_at(chunk_t *chunk, arr2d_dvec3_t arr, arr2d_dvec3_t n, vec2 uv)
{
    size_t size = rand() % 8;
    vec2 uv_a;

    for (size_t i = 0; i < size; i++) {
        uv_a = vec2_add(uv, (vec2){randfn() / 10.0, (double)i / 30.0});
        add_chalet(chunk, arr2d_dvec3_sample_linear(arr, uv_a),
        arr2d_dvec3_sample_linear(n, uv_a));
        uv_a = vec2_add(uv, (vec2){randfn() / 10.0, (double)i / 30.0});
        add_npc(chunk, arr2d_dvec3_sample_linear(arr, uv_a));
    }
        
}

static void add_village(chunk_t *chunk, arr2d_dvec3_t arr, arr2d_dvec3_t n)
{
    if ((rand() % 4) != 0)
        return;
    for (size_t i = 0; i < 64; i++) {
        vec2 uv = {randf(), randf()};
        dvec3 p = arr2d_dvec3_sample_linear(arr, uv);
        dvec3 norm = arr2d_dvec3_sample_linear(n, uv);
        if ((norm.y < 0.82) || (p.y < -40.0))
            continue;
        add_vill_ent_at(chunk, arr, n, uv);
        break;
    }
}

void chunk_detail_terrain(chunk_t *chunk)
{
    arr2d_dvec3_t arr = arr2d_dvec3_copy(chunk->terrain_base);
    chunk_border_t border = chunk_border_fetch(chunk->pos);
    arr2d_dvec3_t n;

    n = split(chunk, &arr, border);
    add_grass(chunk, arr, n);
    add_village(chunk, arr, n);
    arr2d_dvec3_destroy(arr);
    arr2d_dvec3_destroy(n);
    chunk_border_destroy(border);
    entity3_bind_col(chunk->terrain,
    entity3_get_lod_ref(chunk->terrain, WORLD_LOD_MAX));
}
