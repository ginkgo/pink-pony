varying vec3 light;
varying vec3 normal;
varying vec3 eye;

void main (void)
{
    gl_Position = ftransform();
    normal = gl_NormalMatrix * gl_Normal;

    vec4 light_position = gl_LightSource[0].position;
    light = normalize(light_position.xyz);

    eye = (gl_ModelViewMatrix * gl_Vertex).xyz;
    
    gl_FrontColor = gl_Color;
}
