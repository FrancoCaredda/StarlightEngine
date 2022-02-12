#version 450 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 TextureCoord;

uniform mat4 u_Model;
uniform mat4 u_View;

out VertexOut
{
    vec3 Normal;
} vs_vertex_out;

void main()
{
    gl_Position = u_View * u_Model * vec4(aPosition, 1.0);
    vs_vertex_out.Normal = normalize(mat3(transpose(inverse(u_View * u_Model))) * aNormal);
}
