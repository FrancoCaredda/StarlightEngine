#version 450 core

out vec4 FragColor;

in Vertex
{
    vec3 Position;
    vec3 Color;
} vs_vertex;

void main()
{
    FragColor = vec4(vs_vertex.Color, 1.0);
}
