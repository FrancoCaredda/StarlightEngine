#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include "defines.h"

#include "Core/Renderer/IShader.h"
#include "Core/Renderer/IBuffers.h"
#include "Core/Renderer/IVertexArray.h"

#include "Core/enums.h"

namespace Starlight
{
	namespace OpenGL
	{
		class GLRenderer
		{
		public:
			SL_SINGLE_CLASS(GLRenderer);

			static bool Init() noexcept;
			
			static void Enable(Test test) noexcept;
			static void Disable(Test test) noexcept;

			static void Clear(int buffers) noexcept;
			static void ClearColor(const glm::vec4& color);
			static void DrawFrame() noexcept;
			static void DrawPoints(uint32_t count) noexcept;
			static void DrawIndecies(IVertexArray* vertexArray, IIndexBuffer* indexBuffer, IShaderProgram* program) noexcept;

			static void Shutdown() noexcept;

			~GLRenderer() = default;
		private:
			GLRenderer() = default;
			static GLRenderer s_Instance;
			
			bool m_Inited = false;
		};
	}
}

#endif // !OPENGL_RENDERER_H
