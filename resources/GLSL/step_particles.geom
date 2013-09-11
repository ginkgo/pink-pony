#version 120
#extension GL_EXT_geometry_shader4 : enable

varying in vec4 in_pos[];
varying in vec4 in_color[];
varying in vec3 in_vel[];
varying in float in_life[];

varying out vec4 out_pos;
varying out vec4 out_color;
varying out vec3 out_vel;
varying out float out_life;

void main()
{
    if (in_life[0] > 0.0) {
        
        out_pos = in_pos[0];
        out_color = in_color[0];
        out_vel = in_vel[0];
        out_life = in_life[0];
        gl_Position = gl_PositionIn[0];

        EmitVertex();
        EndPrimitive();
    }
}
