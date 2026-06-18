#version 330

uniform float time_diff;
uniform float water_level;
uniform vec3 level_size;
uniform sampler2D heightmap;

layout(location=0) in vec4 pos;
layout(location=1) in vec4 color;
layout(location=2) in vec3 vel;
layout(location=3) in float life;

out vec4 in_pos;
out vec4 in_color;
out vec3 in_vel;
out float in_life;

vec3 calc_normal(vec2 uv, vec3 pos, vec3 level_size) {
    vec3 dx = texture2DLod(heightmap, uv + vec2(0.01,0.0),0.0).rgb * level_size - pos;
    dx.xz = (uv + vec2(0.01,0.0)) * level_size.xz - pos.xz;
    vec3 dy = texture2DLod(heightmap, uv + vec2(0.0,0.01),0.0).rgb * level_size - pos;
    dy.xz = (uv + vec2(0.0,-0.01)) * level_size.xz - pos.xz;

    return normalize(cross(dx,dy));
}

void main (void)
{
    vec3 g = vec3(0.0,-9.81,0.0);

    in_vel = vel + time_diff * g;

    in_life = life - time_diff;
    in_pos = pos + vec4(in_vel,0) * time_diff;
    in_color = color / life * in_life;

    vec2 uv = in_pos.xz / level_size.xz * vec2(1,-1) + vec2(0.5,0.5);

    vec3 pos3 = texture2D(heightmap, uv).rgb * level_size;
    pos3.xz = uv * level_size.xz;


    if (water_level > pos3.y && in_pos.y < water_level ) {
        in_pos.y = water_level;

        in_vel = reflect(in_vel, vec3(0,1,0)) * 0.25;
    } else if (in_pos.y < pos3.y) {
        in_pos.y = pos3.y;

        vec3 normal = calc_normal(uv, pos3, level_size);

        in_vel = reflect(normalize(in_vel), normal) * length(in_vel) * 0.75;
    }

    gl_Position = pos;
}
