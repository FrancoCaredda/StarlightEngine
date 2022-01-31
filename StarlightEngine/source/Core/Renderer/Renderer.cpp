#include "Renderer.h"

#include "Core/Log.h"

namespace Starlight
{
    Renderer Renderer::s_Instance;

    bool Renderer::Init(API rendererApi)
    {
        s_Instance.m_RendererApi = rendererApi;
        return s_Instance.m_Inited = (glewInit() == GLEW_OK);
    }

    void Renderer::DrawTriangle()
    {
        switch (s_Instance.m_RendererApi)
        {
        case OPENGL_API:
            glBegin(GL_TRIANGLES);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(-0.5f, -0.5f, 0.0f);
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(0.0f,   0.5f, 0.0f);
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(0.5f,  -0.5f, 0.0f);
            glEnd();
            break;
        default:
            SL_ERROR("Renderer supports OpenGL now");
            break;
        }
    }
    
    void Renderer::Shutdown()
    {
        SL_STD_EXCEPTION(!s_Instance.m_Inited, "Renderer isn\'t inited!");
    }
}
