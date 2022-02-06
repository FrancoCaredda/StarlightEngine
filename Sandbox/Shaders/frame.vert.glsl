#version 450 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTextureCoord;

out Vertex
{
    vec3 Position;
    vec2 TextureCoord;
} vs_vertex;

void main()
{
    gl_Position = vec4(aPosition, 1.0);
    vs_vertex.Position = aPosition;
    vs_vertex.TextureCoord = aTextureCoord;
}
