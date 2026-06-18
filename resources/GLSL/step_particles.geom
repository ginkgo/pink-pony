#version 330

layout(points) in;
layout(points, max_vertices = 1) out;

in vec4 in_pos[];
in vec4 in_color[];
in vec3 in_vel[];
in float in_life[];

out vec4 out_pos;
out vec4 out_color;
out vec3 out_vel;
out float out_life;

void main()
{
    if (in_life[0] > 0.0) {

        out_pos = in_pos[0];
        out_color = in_color[0];
        out_vel = in_vel[0];
        out_life = in_life[0];
        gl_Position = gl_in[0].gl_Position;

        EmitVertex();
        EndPrimitive();
    }
}
