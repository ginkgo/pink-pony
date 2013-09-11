#version 120
#extension GL_EXT_geometry_shader4 : enable

uniform vec3 up;
uniform vec3 right;

varying out vec2 uv;

void main()
{
	gl_FrontColor = gl_FrontColorIn[0];

	gl_Position = (gl_ModelViewProjectionMatrix 
                   * (gl_PositionIn[0] 
                      + -0.25 * vec4(right,0) +  0.25 * vec4(up,0)));
	uv = vec2(0,1);
    EmitVertex();
	gl_Position = (gl_ModelViewProjectionMatrix 
                   * (gl_PositionIn[0] 
                      + -0.25 * vec4(right,0) + -0.25 * vec4(up,0)));
	uv = vec2(0,0);
    EmitVertex();
	gl_Position = (gl_ModelViewProjectionMatrix 
                   * (gl_PositionIn[0] 
                      +  0.25 * vec4(right,0) +  0.25 * vec4(up,0)));
	uv = vec2(1,1);
    EmitVertex();
	gl_Position = (gl_ModelViewProjectionMatrix 
                   * (gl_PositionIn[0] 
                      +  0.25 * vec4(right,0) + -0.25 * vec4(up,0)));
	uv = vec2(1,0);
    EmitVertex();
	EndPrimitive();
}
