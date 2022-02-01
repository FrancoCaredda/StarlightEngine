#version 450 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aColor;

out Vertex
{
    vec3 Position;
    vec3 Color;
} vs_vertex;

void main()
{
    gl_Position = vec4(aPosition, 1.0);
    vs_vertex.Position = aPosition;
    vs_vertex.Color = aColor;
}
