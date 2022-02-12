#include "IFrameBuffer.h"

#include "Renderer.h"

#include "Core/Log.h"
#include "Core/Platform/OpenGL/FrameBuffer.h"

namespace Starlight
{
	IRenderBuffer* CreateRenderBuffer(Formats format, int width, int height)
	{
		IRenderBuffer* buffer = nullptr;

		switch (Renderer::GetApi())
		{
		case OPENGL_API:
			buffer = new OpenGL::RenderBuffer();
			buffer->Allocate(format, width, height);
			return buffer;
		default:
			SL_ERROR("Starlight engine supports only OpenGL now");
			return nullptr;
		}
	}
	
	IFrameBuffer* CreateFrameBuffer()
	{
		switch (Renderer::GetApi())
		{
		case OPENGL_API:
			return new OpenGL::FrameBuffer();
		default:
			SL_ERROR("Starlight engine supports only OpenGL now");
			return nullptr;
		}
	}
}
