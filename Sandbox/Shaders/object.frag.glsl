#version 450 core

out vec4 FragColor;

uniform sampler2D u_Texture;

in Vertex
{
    vec3 Position;
    vec3 Color;
    vec2 TextureCoord;
} vs_vertex;

void main()
{
    FragColor = texture(u_Texture, vs_vertex.TextureCoord) * vec4(vs_vertex.Color, 1.0);
}
