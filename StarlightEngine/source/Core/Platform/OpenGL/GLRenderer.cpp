#include "GLRenderer.h"

#include "Buffers.h"


namespace Starlight
{
	namespace OpenGL
	{
		GLRenderer GLRenderer::s_Instance;

		bool GLRenderer::Init() noexcept
		{
			s_Instance.m_Inited = (glewInit() == GLEW_OK);

			return s_Instance.m_Inited;
		}

		void GLRenderer::Enable(Test test) noexcept
		{
			glEnable(test);
		}

		void GLRenderer::Disable(Test test) noexcept
		{
			glDisable(test);
		}

		void GLRenderer::Clear(int buffers) noexcept
		{
			glClear(buffers);
		}

		void GLRenderer::ClearColor(const glm::vec4& color)
		{
			glClearColor(color.r, color.g, color.b, color.a);
		}

		void GLRenderer::DrawArrays(int first, int count)
		{
			glDrawArrays(GL_TRIANGLES, first, count);
		}

		void GLRenderer::DrawFrame() noexcept
		{
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}

		void GLRenderer::DrawPoints(uint32_t count) noexcept
		{
			glDrawArrays(GL_POINTS, 0, count);
		}

		void GLRenderer::DrawIndecies(IVertexArray* vertexArray, IIndexBuffer* indexBuffer, IShaderProgram* program) noexcept
		{
			vertexArray->Bind();
			program->Bind();
			glDrawElements(GL_TRIANGLES, dynamic_cast<OpenGL::IndexBuffer*>(indexBuffer)->GetCount(), GL_UNSIGNED_INT, nullptr);
		}

		void GLRenderer::Shutdown() noexcept
		{
			s_Instance.m_Inited = false;
		}
	}
}