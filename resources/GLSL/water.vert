
varying vec3 world_coord;
varying vec3 camera_coord;
varying vec3 normal;

void main (void)
{
    world_coord = gl_Vertex.xyz;
    camera_coord = (gl_ModelViewMatrixInverse * vec4(0,0,0,1)).xyz;
    normal = gl_Normal;
    
    gl_Position = ftransform();
    gl_FrontColor = gl_Color;
}
