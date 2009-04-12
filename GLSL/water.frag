varying vec3 light;
varying vec3 normal; 
varying vec3 eye; 

vec4 diffuse (vec3 l, vec3 n, vec3 v, int light_no)
{
    vec4 color = gl_Color * gl_LightSource[light_no].diffuse;
    
    return color * max(0.0, dot(l, n));
} 

vec4 specular (vec3 l, vec3 n, vec3 v, int light_no)
{
    vec4 color = gl_LightSource[light_no].specular;
    float shininess = gl_FrontMaterial.shininess;

    vec3 h = normalize(l + v);
    
    return color * pow(max(0.0, dot(h, n)),shininess);
}

vec4 velvet (vec3 l, vec3 n, vec3 v, int light_no)
{
    //vec4 color = texture2D(heightmap, gl_TexCoord[0].st);
    vec4 color = diffuse(l,n,v,light_no);
    
    return color * pow(1.0 - max(0.0, dot(v, n)), 0.5);
}

void main (void)
{
    vec3 my_eye = normalize(eye);
    vec4 color = gl_Color;

    //color.a = pow(dot(my_eye, normal),0.25);

    gl_FragColor = color;
}
