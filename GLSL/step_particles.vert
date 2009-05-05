uniform float time_diff;
uniform float water_level;
uniform vec3 level_size;
uniform sampler2D heightmap;

attribute float life;
attribute vec3 vel;

varying vec4 in_pos;
varying vec4 in_color;
varying vec3 in_vel;
varying float in_life;

vec3 calc_normal(vec2 uv, vec3 pos, vec3 level_size) {
    vec3 dx = texture2D(heightmap, uv + vec2(0.01,0.0)).rgb * level_size - pos;
    dx.xz = (uv + vec2(0.01,0.0)) * level_size.xz - pos.xz;
    vec3 dy = texture2D(heightmap, uv + vec2(0.0,0.01)).rgb * level_size - pos;    
    dy.xz = (uv + vec2(0.0,-0.01)) * level_size.xz - pos.xz;

    return normalize(cross(dx,dy));
}

void main (void)
{
    vec3 g = vec3(0.0,-9.81 * 2.0,0.0);

    in_vel = vel + time_diff * g;
    
    in_life = life - time_diff;
    in_pos = gl_Vertex + vec4(in_vel,0) * time_diff;
    in_color = gl_Color / life * in_life;

    vec2 uv = in_pos.xz / level_size.xz * vec2(1,-1) + vec2(0.5,0.5);

    vec3 pos = texture2D(heightmap, uv).rgb * level_size;
    pos.xz = uv * level_size.xz;


    if (water_level > pos.y && in_pos.y < water_level ) {
        in_pos.y = water_level;
        
        in_vel = reflect(in_vel, vec3(0,1,0)) * vec3(0.5,0.25,0.5);
    } else if (in_pos.y < pos.y) {
        in_pos.y = pos.y;
        
        vec3 normal = calc_normal(uv, pos, level_size);
        
        in_vel = reflect(in_vel, normal) * vec3(0.8,0.75,0.8);
    }
    
    gl_Position = gl_Vertex;
}
