#version 450 core

layout(triangles) in;
layout(line_strip, max_vertices = 6) out;

in VertexOut
{
    vec3 Normal;
} gs_vertex_in[];

uniform mat4 u_Projection;
uniform float u_Magnitude;

void DrawNormal(int index)
{
    gl_Position = u_Projection * gl_in[index].gl_Position;
    EmitVertex();

    gl_Position =  u_Projection * (gl_in[index].gl_Position + 
                    vec4(gs_vertex_in[index].Normal, 0.0) * u_Magnitude);
    EmitVertex();
    EndPrimitive();
}

void main()
{
    DrawNormal(0);
    DrawNormal(1);
    DrawNormal(2);
}
