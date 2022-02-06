#version 450 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTextureCoord;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

out Vertex
{
    vec3 Position;
    vec3 Color;
    vec2 TextureCoord;
} vs_vertex;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * vec4(aPosition, 1.0);
    vs_vertex.Position = aPosition;
    vs_vertex.Color = aColor;
    vs_vertex.TextureCoord = aTextureCoord;
}
