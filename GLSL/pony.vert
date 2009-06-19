varying vec3 light;
varying vec3 normal;
varying vec3 eye;

uniform mat4 bone_transforms[31];

attribute vec4 bones;
attribute vec4 weights;

void main (void)
{
    vec4 my_normal = vec4(0,0,0,0);//vec4(gl_Normal,0);
    vec4 my_vertex = vec4(0,0,0,0);//glVertex;

    int bone = int(bones.x);
    vec4 v = bone_transforms[bone] * gl_Vertex;
    vec4 n = bone_transforms[bone] * vec4(gl_Normal,0);

    my_normal = my_normal + n * weights.x;
    my_vertex = my_vertex + v * weights.x;

    bone = int(bones.y);
    v = bone_transforms[bone] * gl_Vertex;
    n = bone_transforms[bone] * vec4(gl_Normal,0);

    my_normal = my_normal + n * weights.y;
    my_vertex = my_vertex + v * weights.y;

    bone = int(bones.z);
    v = bone_transforms[bone] * gl_Vertex;
    n = bone_transforms[bone] * vec4(gl_Normal,0);

    my_normal = my_normal + n * weights.z;
    my_vertex = my_vertex + v * weights.z;

    bone = int(bones.w);
    v = bone_transforms[bone] * gl_Vertex;
    n = bone_transforms[bone] * vec4(gl_Normal,0);

    my_normal = my_normal + n * weights.w;
    my_vertex = my_vertex + v * weights.w;

    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * my_vertex;
    normal = gl_NormalMatrix * my_normal.xyz;

    vec4 light_position = gl_LightSource[0].position;
    light = normalize(light_position.xyz);

    eye = (gl_ModelViewMatrix * gl_Vertex).xyz;
    
    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_FrontColor = gl_Color;
}
