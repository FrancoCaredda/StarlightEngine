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

    void Renderer::Clear() noexcept
    {
        switch (s_Instance.m_RendererApi)
        {
        case OPENGL_API:
            OpenGL::GLRenderer::Clear();
            break;
        default:
            SL_ERROR("Renderer supports OpenGL now");
            break;
        }
    }

    void Renderer::ClearColor(const glm::vec4& color) noexcept
    {
        switch (s_Instance.m_RendererApi)
        {
        case OPENGL_API:
            OpenGL::GLRenderer::ClearColor(color);
            break;
        default:
            SL_ERROR("Renderer supports OpenGL now");
            break;
        }
    }

    void Renderer::DrawIndecies(IVertexArray* vertexArray, IIndexBuffer* indexBuffer, IShaderProgram* program)
    {
        program->SetUniformMat4f("u_Projection", s_Instance.m_Projection);
        program->SetUniformMat4f("u_View", s_Instance.m_Camera->GetView());

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

    void Renderer::SetMainCamera(Camera* camera) noexcept
    {
        s_Instance.m_Camera = camera;
    }

    void Renderer::SetProjection(const glm::mat4& projection) noexcept
    {
        s_Instance.m_Projection = projection;
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
