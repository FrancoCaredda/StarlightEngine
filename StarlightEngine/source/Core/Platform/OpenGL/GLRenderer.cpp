#include "GLRenderer.h"

#include "Buffers.h"

namespace Starlight
{
	namespace OpenGL
	{
		GLRenderer GLRenderer::s_Instance;

		bool GLRenderer::Init() noexcept
		{
			return s_Instance.m_Inited = (glewInit() == GLEW_OK);
		}

		void GLRenderer::DrawIndecies(IVertexArray* vertexArray, IIndexBuffer* indexBuffer, IShaderProgram* program) noexcept
		{
			vertexArray->Bind();
			program->Bind();
			glDrawElements(GL_TRIANGLES, dynamic_cast<OpenGL::IndexBuffer*>(indexBuffer)->GetCount(), GL_UNSIGNED_INT, NULL);
		}

		void GLRenderer::Shutdown() noexcept
		{

		}
	}
}