
uniform sampler2D sky;
uniform sampler2D noise;

uniform vec3 eye_pos;

uniform float camera_far;

uniform vec3 water_color;

uniform float time;

varying vec3 world_coord;
varying vec3 camera_coord;
varying vec3 normal;

#define M_2_PI 6.28318530718
#define M_PI (M_2_PI * 0.5)
#define M_PI_2 (M_2_PI * 0.25)

float dispf(vec2 p)
{
    return sin(texture2D(noise,p * 0.005).r * 10 + time) + (sin(p.x * 0.2 + time) + cos(p.y * 0.2 + time)) * 0.5; 
}

vec3 displacement(vec3 wp, float dist)
{
    return wp + normal * (dispf(wp.xz) * min(1,2/pow(dist,1)) * 0.5 + 0.5) * 4;
}

void main (void)
{
    vec3 V = normalize(camera_coord - world_coord);
    float dist = distance(camera_coord, world_coord);

    
    vec3 D = displacement(world_coord, dist);
    vec3 dDdx = displacement(world_coord + vec3(0.01,0,0), dist) - D;
    vec3 dDdz = displacement(world_coord + vec3(0,0,0.01), dist) - D;

    vec3 N = normalize(cross(dDdz, dDdx));
    
    
    vec3 r = reflect(V, N);
    float phi = atan(r.z, r.x);
    float eta = atan(r.y, length(r.xz));
    vec3 s = texture2D(sky, vec2(phi / M_2_PI + 0.25, eta / M_PI + 0.5));
    
    float R  = pow(1-dot(V,N),6);

    if (gl_Color.a < 1.0) {
        
        gl_FragColor = vec4(s, R * 0.8);

        if (dist > camera_far * (1 - world_coord.y / camera_coord.y) * 0.9) {
            vec4 C = vec4(water_color,0*gl_Color.a);
            gl_FragColor = vec4(mix(C,gl_FragColor,gl_FragColor.a).xyz,1);
        }
    } else {
        gl_FragColor = vec4(water_color,1) ;
    }

}
