#version 330

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

uniform vec3 up;
uniform vec3 right;
uniform mat4 mvp;

in vec4 in_color[];

out vec2 out_uv;
out vec4 out_color;

void main()
{
	out_color = in_color[0];

	gl_Position = (mvp
                   * (gl_in[0].gl_Position
                      + -0.25 * vec4(right,0) +  0.25 * vec4(up,0)));
	out_uv = vec2(0,1);
    EmitVertex();
	gl_Position = (mvp
                   * (gl_in[0].gl_Position
                      + -0.25 * vec4(right,0) + -0.25 * vec4(up,0)));
	out_uv = vec2(0,0);
    EmitVertex();
	gl_Position = (mvp
                   * (gl_in[0].gl_Position
                      +  0.25 * vec4(right,0) +  0.25 * vec4(up,0)));
	out_uv = vec2(1,1);
    EmitVertex();
	gl_Position = (mvp
                   * (gl_in[0].gl_Position
                      +  0.25 * vec4(right,0) + -0.25 * vec4(up,0)));
	out_uv = vec2(1,0);
    EmitVertex();
	EndPrimitive();
}
