#version 330
uniform sampler2D texture;

in vec2 out_uv;
in vec4 out_color;

void main()
{
    vec4 t = texture2D(texture, out_uv);

    gl_FragColor = out_color * t;

}
