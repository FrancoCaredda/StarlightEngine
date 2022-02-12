#include "IVertexArray.h"

#include "Core/Platform/OpenGL/VertexArray.h"
#include "Core/Log.h"
#include "Renderer.h"

namespace Starlight
{
	IVertexArray* CreateVertexArray() noexcept
	{
		switch (Renderer::GetApi())
		{
		case OPENGL_API:
			return new OpenGL::VertexArray();
		default:
			SL_ERROR("Starlight engine supports only OpenGL now");
			return nullptr;
		}
	}
}