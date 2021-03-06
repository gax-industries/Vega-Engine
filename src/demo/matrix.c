/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** demo_matrix
*/

#include "headers.h"

static void send_uniform(void)
{
    gluint u;
    vec3 light = dvec3_vec3(dvec3_muls(_demo->world.light_dir, -1.0));
    vec3 p = dvec3_vec3(dmat4_trans(_demo->world.camera->trans.world));
    vec3 off = vec3_init(sin(_demo->clocks.t / 3.0f) / 10.0f, 0.0,
    cos(_demo->clocks.t * 3.14f / 3.0f) / 10.0f);

    for (size_t i = 0; i < SHADER_MAX; i++) {
        glUseProgram(_demo->shader[i].program);
        u = glGetUniformLocation(_demo->shader[i].program, "l_dir");
        glUniform3fv(u, 1, (void*)&light);
        u = glGetUniformLocation(_demo->shader[i].program, "p_cam");
        glUniform3fv(u, 1, (void*)&p);
    }
    glUseProgram(_demo->shader[SHADER_VEG].program);
    glUniform3fv(_demo->shader[SHADER_VEG].uniform[3], 1, (void*)&off);
}

static void update_culling(shader_t shader)
{
    if (_demo->buf.cull_state != _demo->shader[shader].do_cull) {
        if (_demo->buf.cull_state)
            glEnable(GL_CULL_FACE);
        else
            glDisable(GL_CULL_FACE);
        _demo->buf.cull_state = _demo->shader[shader].do_cull;
    }
}

void shader_set(shader_t shader, dmat4 mvp, dmat4 world, dmat4 rot)
{
    mat4 mvp_actual;
    mat4 world_actual;
    mat4 rot_actual;

    dmat4_mat4(mvp, mvp_actual);
    dmat4_mat4(world, world_actual);
    dmat4_mat4(rot, rot_actual);
    glUseProgram(_demo->shader[shader].program);
    glUniformMatrix4fv(_demo->shader[shader].uniform[0],
    1, GL_FALSE, (void*)mvp_actual);
    glUniformMatrix4fv(_demo->shader[shader].uniform[1],
    1, GL_FALSE, (void*)world_actual);
    glUniformMatrix4fv(_demo->shader[shader].uniform[2],
    1, GL_FALSE, (void*)rot_actual);
    update_culling(shader);
}

void refresh_vp(demo_t *demo)
{
    proj_t proj_struct = {0.3f, 4094.0f * 4, 90.0f, 16.0f / 9.0f};
    proj_t ortho_struct = proj_struct;

    ortho_struct.fov_w = 10.0f;
    if (demo->cam.proj == PROJ_TYPE_PERSPECTIVE)
        dmat4_perspective(proj_struct, demo->cam.mvp.proj);
    else
        dmat4_ortho(ortho_struct, demo->cam.mvp.proj);
    entity3_update_trans_inv(demo->world.camera);
    dmat4_copy(demo->world.camera->trans.world_inv, demo->cam.mvp.view);
    dmat4_mul(demo->cam.mvp.proj, demo->cam.mvp.view, demo->cam.mvp.vp);
    send_uniform();
}
