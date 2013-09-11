uniform vec3 hemi_pole;
uniform vec4 hemi_sky;
uniform vec4 hemi_ground;

varying vec3 light;
varying vec3 normal;
varying vec3 eye;


vec4 basecolor()
{
    return vec4(1,0,0,1);
}

vec4 diffuse (vec3 l, vec3 n, vec3 v, int light_no)
{
    
    vec4 color = gl_LightSource[light_no].diffuse;
    
    return color * max(0.0, dot(l, n)) * 1.3;
} 

vec4 specular (vec3 l, vec3 n, vec3 v, int light_no)
{
    
    vec4 color = gl_LightSource[light_no].specular;
    
    vec3 h = normalize(l + v);
    
    return color * smoothstep(0.45, 0.55, pow(max(0.0, dot(h, n)), 10.0));
} 

vec4 hemisphere (vec3 n)
{
    vec3 p = gl_NormalMatrix * hemi_pole;

    float cos_phi = dot(n, p);
    float i = 0.5 + (0.5 * cos_phi);

    return mix(hemi_ground, hemi_sky, i);
}

void main (void)
{
    vec3 my_normal = normalize(normal);
    vec3 my_eye = normalize(eye);

    vec4 hemi = hemisphere (my_normal);
    vec4 diff = diffuse(light, my_normal, -my_eye, 0);
    vec4 col = hemi + diff;
    
    gl_FragColor = basecolor() * col  + specular(light, my_normal, -my_eye, 0);
}
