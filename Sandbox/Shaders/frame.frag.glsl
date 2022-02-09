#version 450 core

out vec4 FragColor;

uniform sampler2D u_Texture;

in Vertex
{
    vec3 Position;
    vec2 TextureCoord;
} vs_vertex;

void main()
{
    vec4 color = texture(u_Texture, vs_vertex.TextureCoord);
    FragColor = color;
}
