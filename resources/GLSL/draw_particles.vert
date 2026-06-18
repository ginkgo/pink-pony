#version 330

layout(location=0) in vec4 pos;
layout(location=1) in vec4 color;

out vec4 in_color;

void main()
{
    gl_Position = pos;
    in_color = color;
}
