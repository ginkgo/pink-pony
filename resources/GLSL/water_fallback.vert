
uniform vec3 water_color;
varying vec4 color;

void main (void)
{   
    gl_Position = ftransform();
    color = vec4(water_color, gl_Color.a);
}
