varying vec4 out_pos;
varying vec4 out_color;
varying vec3 out_vel;
varying float out_life;

void main (void)
{
    gl_FragColor = out_life * vec4(out_vel,1) * out_pos * out_color;
}
