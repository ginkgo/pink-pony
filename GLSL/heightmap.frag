uniform sampler2D sand;
uniform sampler2D grass;
uniform sampler2D noise;

uniform float water_level;

uniform vec3 start;
uniform vec3 end;

uniform vec3 hemi_pole;
uniform vec4 hemi_sky;
uniform vec4 hemi_ground;

uniform float velvet_coeff;

varying vec3 eye;
varying vec3 light;
varying vec3 normal;
varying vec3 world_coord;


vec4 basecolor()
{
    float t = smoothstep(water_level + 5.0,
                         water_level + 7.0, world_coord.y);

    vec4 color = vec4(0,0,0,0);

    if (t > 0.0) {
        color = color + t * texture2D(grass, world_coord.xz * 0.05);
    }

    if (t < 1.0) {
        color = color + (1-t) * texture2D(sand, world_coord.xz * 0.05);
    }

    return color;
}

vec4 diffuse (vec3 l, vec3 n, vec3 v, int light_no)
{
    
    vec4 color = gl_LightSource[light_no].diffuse;
    
    return color * max(0.0, dot(l, n)) * 1.3;
} 

vec4 hemisphere (vec3 n)
{
    vec3 p = gl_NormalMatrix * hemi_pole;

    float cos_phi = dot(n, p);
    float i = 0.5 + (0.5 * cos_phi);

    return mix(hemi_ground, hemi_sky, i);
}

float velvet (vec3 l, vec3 n, vec3 v, float exp)
{    
    return velvet_coeff * 2.0 * pow(1.0 - max(0.0, dot(v, n)), exp);
}

void main (void)
{
    vec3 my_normal = normalize(normal);
    vec3 my_eye = normalize(eye);

    vec4 hemi = hemisphere (my_normal);

    float t = smoothstep(water_level + 5.65,
                         water_level + 6.35,
                         world_coord.y +
                         3 * texture2D(noise, world_coord.xz * 0.005).r);

    
    gl_FragColor = vec4(0,0,0,0);

    if (world_coord.y > water_level + 2.0) {
        gl_FragColor = t * texture2D(grass, world_coord.xz * 0.05) 
                         * (diffuse(light, my_normal, -my_eye, 0)
                            + hemi * velvet(light, my_normal, -my_eye, 7.0) * 0.5
                            + hemi);
    }
/*     else { */
/*         gl_FragColor = vec4(1,0,0,1); */
/*     } */

    if (world_coord.y < water_level + 7.0) {
        gl_FragColor = gl_FragColor
            + (1-t)
            * texture2D(sand, world_coord.xz * 0.025) 
            * (diffuse(light, my_normal, -my_eye, 0) * 0.75
               + hemi * velvet(light, my_normal, -my_eye, 25.0) * -0.2 
               + hemi * 1.0);
    }
/*     else { */
/*         gl_FragColor += vec4(0,0,1,1); */
/*     } */

    if (world_coord.y < water_level) {
        gl_FragColor =
            mix(gl_FragColor, vec4(65.0/255.0,105.0/255.0,225.0/255.0,1),
                pow((water_level - world_coord.y) / water_level, 0.5));
        
    }

/*     gl_FragColor = basecolor() * (diffuse(light, my_normal, -my_eye, 0) */
/*                                   + hemi * velvet(light, my_normal, -my_eye, 0) */
/*                                   + hemi); */
}
