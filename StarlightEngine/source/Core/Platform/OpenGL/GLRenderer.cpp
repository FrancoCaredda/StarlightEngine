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

			if (s_Instance.m_Inited)
				glEnable(GL_DEPTH_TEST);

			return s_Instance.m_Inited;
		}

		void GLRenderer::Clear() noexcept
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void GLRenderer::ClearColor(const glm::vec4& color)
		{
			glClearColor(color.r, color.g, color.b, color.a);
		}

		void GLRenderer::DrawIndecies(IVertexArray* vertexArray, IIndexBuffer* indexBuffer, IShaderProgram* program) noexcept
		{
			vertexArray->Bind();
			program->Bind();
			glDrawElements(GL_TRIANGLES, dynamic_cast<OpenGL::IndexBuffer*>(indexBuffer)->GetCount(), GL_UNSIGNED_INT, NULL);
		}

		void GLRenderer::Shutdown() noexcept
		{
			if (s_Instance.m_Inited)
				glDisable(GL_DEPTH_TEST);
		}
	}
}