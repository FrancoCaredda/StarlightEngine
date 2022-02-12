#define VIEW_PROJECTION_BINDING 0

layout(std140, binding = 0) uniform ViewProjection
{
    mat4 u_Projection;
    mat4 u_View;
};
