#include "IBuffers.h"

#include "Core/Renderer/Renderer.h"
#include "Core/Platform/OpenGL/Buffers.h"
#include "Core/Log.h"

namespace Starlight
{
	IVertexBuffer* CreateVertexBuffer() noexcept
	{
		switch (Renderer::GetApi())
		{
		case OPENGL_API:
			return new OpenGL::VertexBuffer(GL_STATIC_DRAW);
		default:
			SL_ERROR("Starlight engine supports only OpenGL now");
			return nullptr;
		}
	}

	IIndexBuffer* CreateIndexBuffer() noexcept
	{
		switch (Renderer::GetApi())
		{
		case OPENGL_API:
			return new OpenGL::IndexBuffer(GL_STATIC_DRAW);
		default:
			SL_ERROR("Starlight engine supports only OpenGL now");
			return nullptr;
		}
	}
}