
uniform sampler2D sky;
uniform sampler2D noise;

uniform vec3 eye_pos;
uniform float camera_far;
uniform float time;

varying vec4 color;

void main (void)
{

    gl_FragColor = color;
}
