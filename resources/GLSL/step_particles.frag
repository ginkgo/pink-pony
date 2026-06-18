#version 330

in vec4 out_pos;
in vec4 out_color;
in vec3 out_vel;
in float out_life;

void main (void)
{
    gl_FragColor = out_life * vec4(out_vel,1) * out_pos * out_color;
}
