uniform sampler2D texture;

uniform vec3 hemi_pole;
uniform vec4 hemi_sky;
uniform vec4 hemi_ground;

uniform float velvet_coeff;

varying vec3 light;
varying vec3 normal;
varying vec3 eye;


vec4 basecolor()
{
    return texture2D(texture, gl_TexCoord[0].st);
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

float velvet (vec3 l, vec3 n, vec3 v, int light_no)
{    
    return velvet_coeff * 2.0 * pow(1.0 - max(0.0, dot(v, n)), 7.0);
}

void main (void)
{
    vec3 my_normal = normalize(normal);
    vec3 my_eye = normalize(eye);

    vec4 hemi = hemisphere (my_normal);
    
    gl_FragColor = basecolor() * (diffuse(light, my_normal, -my_eye, 0)
                                  + hemi * velvet(light, my_normal, -my_eye, 0)
                                  + hemi);
}
