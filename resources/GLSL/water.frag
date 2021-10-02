
uniform sampler2D sky;
uniform sampler2D noise;

uniform vec3 eye_pos;

uniform float camera_far;

uniform vec3 water_color;

uniform float time;

varying vec3 world_coord;
varying vec3 camera_coord;
varying vec3 normal;
varying vec4 color;

#define M_2_PI 6.28318530718
#define M_PI (M_2_PI * 0.5)
#define M_PI_2 (M_2_PI * 0.25)

float dispf(vec2 p)
{
    return sin(texture2D(noise,p * 0.005).r * 10.0 + time) + (sin(p.x * 0.2 + time) + cos(p.y * 0.2 + time)) * 0.5; 
}

vec3 displacement(vec3 wp, float dist)
{
    return wp + normal * (dispf(wp.xz) * min(1.0,2.0/dist) * 0.5 + 0.5) * 4.0;
}

void main (void)
{
    if (color.a >= 0.999) {
        gl_FragColor = vec4(water_color,1);
        return;
    }
    
    vec3 V = normalize(camera_coord - world_coord);
    float dist = distance(camera_coord, world_coord);

    
    vec3 D = displacement(world_coord, dist);
    vec3 dDdx = displacement(world_coord + vec3(0.5,0,0), dist) - D;
    vec3 dDdz = displacement(world_coord + vec3(0,0,0.5), dist) - D;

    vec3 N = normalize(cross(dDdz, dDdx));
    
    
    vec3 r = reflect(V, N);
    float phi = atan(r.z, r.x);
    float eta = atan(r.y, length(r.xz));
    vec3 s = texture2D(sky, vec2(phi / M_2_PI + 0.25, eta / M_PI + 0.5)).xyz;
    
    float R  = pow(1.0-dot(V,N),6.0);
        
    gl_FragColor = vec4(s, R * 0.8);

    if (dist > camera_far * (1.0 - world_coord.y / camera_coord.y) * 0.9) {
        vec4 C = vec4(water_color,0.0);
        gl_FragColor = vec4(mix(C,gl_FragColor,gl_FragColor.a).xyz,1);
    }

}
