#version 450 core

#include Shaders/includes/material.glsl

out vec4 FragColor;

uniform Material u_Material;

in Vertex
{
    vec3 Position;
    vec3 Normal;
    vec2 TextureCoord;
} vs_vertex;

void main()
{
    FragColor = texture(u_Material.Diffuse, vs_vertex.TextureCoord) * texture(u_Material.Specular, vs_vertex.TextureCoord);
}
