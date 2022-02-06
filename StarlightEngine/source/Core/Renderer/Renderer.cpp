#include "Renderer.h"

#include "Core/Log.h"
#include "Core/Platform/OpenGL/GLRenderer.h"
#include "Core/Renderer/ShaderLibrary.h"

namespace Starlight
{
    Renderer Renderer::s_Instance;

    bool Renderer::Init(API rendererApi, int width, int height)
    {
        s_Instance.m_RendererApi = rendererApi;

      /*  std::vector<float> quad = {
                -1.0f, -1.0f, 1.0f,     0.0f, 0.0f,
                -1.0f,  1.0f, 1.0f,     0.0f, 1.0f,
                 1.0f,  0.0f, 1.0f,     1.0f, 0.0f,
                 1.0f,  1.0f, 1.0f,     1.0f, 1.0f
        };

        std::vector<uint32_t> quadIndecies = { 0, 1, 2, 2, 1, 3 };*/

        switch (rendererApi)
        {
        case OPENGL_API:
            s_Instance.m_Inited = OpenGL::GLRenderer::Init();

            /*s_Instance.m_FrameBuffer = CreateFrameBuffer();
            s_Instance.m_FrameBuffer->Bind();
            s_Instance.m_RenderBuffer = CreateRenderBuffer();
            s_Instance.m_RenderBuffer->Bind();
            s_Instance.m_ColorBuffer = CreateTexture2D(width, height);
            s_Instance.m_ColorBuffer->Bind();
            s_Instance.m_RenderBuffer->Allocate(DEPTH24_STENCIL8, width, height);

            s_Instance.m_FrameBuffer->AttachColorBuffer(s_Instance.m_ColorBuffer, COLOR_ATTACHMENT0);
            s_Instance.m_FrameBuffer->AttachRenderBuffer(s_Instance.m_RenderBuffer, DEPTH_STENCIL_ATTACHMENT);

            if (!s_Instance.m_FrameBuffer->Check())
            {
                SL_FATAL("standard frame buffer isn\'t initialized!");
                return s_Instance.m_Inited = false;
            }

            s_Instance.m_FrameVBO = CreateVertexBuffer();
            s_Instance.m_FrameVBO->Allocate(quad.size() * sizeof(float));
            s_Instance.m_FrameVBO->Write(quad.data(), quad.size() * sizeof(float), 0);

            s_Instance.m_FrameIBO = CreateIndexBuffer();
            s_Instance.m_FrameIBO->Allocate(quadIndecies.size() * sizeof(uint32_t));
            s_Instance.m_FrameIBO->Write(quadIndecies, quadIndecies.size() * sizeof(uint32_t), 0);

            s_Instance.m_FrameVAO = CreateVertexArray();
            s_Instance.m_FrameVAO->SetVertexLayout({
                {0, {3, 5 * sizeof(float), 0}},
                {1, {2, 5 * sizeof(float), 3 * sizeof(float)}}
            });
            s_Instance.m_FrameVAO->SetIndexBuffer(s_Instance.m_FrameIBO);
            s_Instance.m_FrameVAO->AttachVertexBuffer(s_Instance.m_FrameVBO);

            if (!ShaderLibrary::CreateShaderProgram("frame", "Shaders/frame.vert.glsl", "Shaders/frame.frag.glsl"))
            {
                SL_FATAL("standard frame buffer isn\'t initialized!");
                return s_Instance.m_Inited = false;
            }

            s_Instance.m_FrameShader = ShaderLibrary::GetShaderProgram("frame");*/

            return s_Instance.m_Inited;
        default:
            SL_ERROR("Starlight supports OpenGL now");
            return s_Instance.m_Inited = false;
        }
    }

    void Renderer::Enable(Test test) noexcept
    {
        switch (s_Instance.m_RendererApi)
        {
        case OPENGL_API:
            OpenGL::GLRenderer::Enable(test);
            break;
        default:
            SL_ERROR("Renderer supports OpenGL now");
            break;
        }
    }

    void Renderer::Disable(Test test) noexcept
    {
        switch (s_Instance.m_RendererApi)
        {
        case OPENGL_API:
            OpenGL::GLRenderer::Disable(test);
            break;
        default:
            SL_ERROR("Renderer supports OpenGL now");
            break;
        }
    }

    void Renderer::Clear(int buffers) noexcept
    {
        switch (s_Instance.m_RendererApi)
        {
        case OPENGL_API:
            OpenGL::GLRenderer::Clear(buffers);
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

    void Renderer::DrawTexture(IVertexArray* vertexArray, IIndexBuffer* indexBuffer, IShaderProgram* program)
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

    void Renderer::DrawFrameBuffer() noexcept
    {
        s_Instance.m_FrameVBO->Bind();
        s_Instance.m_FrameIBO->Bind();
        s_Instance.m_FrameVAO->Bind();
        s_Instance.m_FrameShader->Bind();

        s_Instance.m_ColorBuffer->SetActiveSlot(0);
        s_Instance.m_ColorBuffer->Bind();
        s_Instance.m_FrameShader->SetUniformi("u_Texture", 0);

        switch (s_Instance.m_RendererApi)
        {
        case OPENGL_API:
            OpenGL::GLRenderer::DrawFrame();
            break;
        default:
            SL_ERROR("Renderer supports OpenGL now");
            break;
        }
    }

    void Renderer::BindStdFrameBuffer() noexcept
    {
        s_Instance.m_FrameBuffer->Bind();
    }

    void Renderer::UnbindStdFrameBuffer() noexcept
    {
        s_Instance.m_FrameBuffer->Unbind();
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

        delete s_Instance.m_FrameBuffer;
        delete s_Instance.m_RenderBuffer;
        delete s_Instance.m_ColorBuffer;
        delete s_Instance.m_FrameIBO;
        delete s_Instance.m_FrameVAO;
        delete s_Instance.m_FrameVBO;

        s_Instance.m_FrameBuffer  = nullptr;
        s_Instance.m_RenderBuffer = nullptr;
        s_Instance.m_ColorBuffer  = nullptr;
        s_Instance.m_FrameIBO     = nullptr;
        s_Instance.m_FrameVAO     = nullptr;
        s_Instance.m_FrameVBO     = nullptr;
    }
}
