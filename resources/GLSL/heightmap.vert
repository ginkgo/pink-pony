varying vec3 eye;
varying vec3 light;
varying vec3 normal; 
varying vec3 world_coord;


void main (void)
{
    normal = gl_NormalMatrix * gl_Normal;

    vec4 light_position = gl_LightSource[0].position;
    light = normalize(light_position.xyz);

    world_coord = gl_Vertex.xyz;
    //gl_ClipVertex = gl_Vertex;
    
    gl_Position = ftransform();

    eye = (gl_ModelViewMatrix * gl_Vertex).xyz;
}
