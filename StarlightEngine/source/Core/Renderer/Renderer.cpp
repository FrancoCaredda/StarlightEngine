#include "Renderer.h"

#include "Core/Log.h"
#include "Core/Platform/OpenGL/GLRenderer.h"

namespace Starlight
{
    Renderer Renderer::s_Instance;

    bool Renderer::Init(API rendererApi)
    {
        s_Instance.m_RendererApi = rendererApi;

        switch (rendererApi)
        {
        case OPENGL_API:
            return s_Instance.m_Inited = OpenGL::GLRenderer::Init();
        default:
            SL_ERROR("Starlight supports OpenGL now");
            return s_Instance.m_Inited = false;
        }
    }

    void Renderer::DrawIndecies(IVertexArray* vertexArray, IIndexBuffer* indexBuffer, IShaderProgram* program)
    {
        switch (s_Instance.m_RendererApi)
        {
        case OPENGL_API:
            OpenGL::GLRenderer::DrawIndecies(vertexArray, indexBuffer, program);
            break;
        default:
            SL_ERROR("Renderer supports OpenGL now");
            break;
        }
    }
    
    void Renderer::Shutdown()
    {
        SL_STD_EXCEPTION(!s_Instance.m_Inited, "Renderer isn\'t inited!");

        switch (s_Instance.m_RendererApi)
        {
        case OPENGL_API:
            OpenGL::GLRenderer::Shutdown();
            break;
        default:
            SL_ERROR("Starlight supports OpenGL now");
            break;
        }
    }
}
