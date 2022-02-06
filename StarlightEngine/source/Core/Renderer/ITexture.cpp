#include "ITexture.h"

#include "Core/Renderer/Renderer.h"
#include "Core/Platform/OpenGL/Texture.h"
#include "Core/Log.h"

namespace Starlight
{
	STARLIGHT_API ITexture2D* CreateTexture2D(Formats format, int width, int height)
	{
		ITexture2D* texture;

		switch (Renderer::GetApi())
		{
		case OPENGL_API:
			texture = new OpenGL::Texture2D();
			texture->Allocate(format, width, height);
			return texture;
		default:
			SL_ERROR("Starlight engine supports only OpenGL now");
			return (texture = nullptr);
		}
	}

	STARLIGHT_API ITexture2D* CreateTexture2D(Formats format, const std::string& filepath)
	{
		ITexture2D* texture;

		switch (Renderer::GetApi())
		{
		case OPENGL_API:
			texture = new OpenGL::Texture2D();
			texture->Load(format, filepath);
			return texture;
		default:
			SL_ERROR("Starlight engine supports only OpenGL now");
			return (texture = nullptr);
		}
	}
}
