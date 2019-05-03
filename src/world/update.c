/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** swaggy demo
*/

#include "headers.h"

double world_get_ground_level(dvec3 p, double bias)
{
    inter_ray3 inter = world_inter((ray3){dvec3_init(p.x, 4096.0, p.z),
    dvec3_init(0.0, -1.0, 0.0)});

    if (inter.triangle == NULL)
        return 64000.0;
    else
        return inter.p.y + bias;
}

static void spawn_at(chunk_t *chunk, dvec3 pos)
{
    entity3 *ent;
    entity3_tag_enemy_data_t *data;

    ent = world_add_entity();
    ent->trans.is_physics = 1;
    ent->trans.is_static = 0;
    ent->trans.is_collision = 1;
    ent->trans.slide_threshold = 0.85;
    ent->trans.pos = dvec3_add(dmat4_trans(chunk->ents->trans.world),
    dvec3_init(pos.x, 1024.0, pos.z));
    ent->trans.speed = dvec3_init(0.0, -10.0, 0.0);
    entity3_set_tag(ent, ENTITY3_TAG_ENEMY);
    data = ent->tag_data;
    data->chunk = chunk->pos;
    data->max_speed = 4.0 + randf() * 4.0;
    data->a_vel = 2.0 + randf() * 4.0;
    entity3_trans_update(ent);
    ent->trans.pos.y = world_get_ground_level(ent->trans.pos, 0.1);
    data->spawn = ent->trans.pos;
    entity3_add_trigger(ent, trigger_create(dvec3_init(-1.0, 0.0, -1.0),
    dvec3_init(1.0, 1.0, 1.0), TRIGGER_ON_HIT_NONE));
    entity3_trans_update(ent);
    ent = entity3_create(ent);
    entity3_set_render(ent, 0, mesh_full_ref_bank_init(MESH_BANK_ENEMY1),
    MATERIAL_GRASS);
    ent->trans.scale = dvec3_init(0.04, 0.04, 0.04);
    entity3_trans_update(ent);
    ent->trans.is_static = 0;
    ent->lod_dist = RENDER_OBJ_LOD_DIST_FAR;
    data->atk = chunk_get_strength(chunk->pos) * 30.0;
    chunk->enemy_count++;
}

static int spawn_group(chunk_t *chunk, dvec3 pos)
{
    size_t c = rand() % 4;

    if (world_get_ground_level(pos, 0.0) < 0.0)
        return 0;
    for (size_t i = 0; i < c; i++)
        spawn_at(chunk, dvec3_add(pos,
        dvec3_init((randf() - 0.5) * 8.0, 0.0, (randf() - 0.5) * 8.0)));
    return 1;
}

static void update_enemy_chunk(chunk_t *chunk)
{
    dvec3 player;
    dvec3 spawn_point;

    if (chunk->is_stalled)
        return;
    player = dmat4_trans(_demo->world.player->trans.world);
    player.y = 0.0;
    while (chunk->enemy_count < chunk->enemy_count_max) {
        spawn_point = dvec3_init(randf() * CHUNK_SIZE, 0.0, randf() * CHUNK_SIZE);
        if (dvec3_dist(player, spawn_point) < CHUNK_SIZE / 4.0)
            continue;
        if (!spawn_group(chunk, spawn_point))
            return;
    }
}

static void chunk_update(chunk_t *chunk)
{
    if (chunk->is_stalled)
        return;
    update_enemy_chunk(chunk);
    entity3_update(chunk->ents);
    if (chunk->ents_ext != NULL)
        entity3_update(chunk->ents_ext);
    while (chunk->ents_global->sub.count > 0)
        entity3_move(chunk->ents_global->sub.ent[0], _demo->world.ents);
}

void world_update(void)
{
    world_chunk_god();
    for (size_t i = 0; i < _demo->world.chunk_count; i++)
        chunk_update(_demo->world.chunk[i]);
    entity3_global_update(_demo->world.ents);
    world_update_triggers();
    refresh_vp(_demo);
}
