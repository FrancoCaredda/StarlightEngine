#include "IShader.h"

#include "Renderer.h"

#include "Core/Log.h"
#include "Core/Platform/OpenGL/Shader.h"

namespace Starlight
{
	IShaderProgram* CreateProgram(const std::string& vertexShader, const std::string& fragmentShader)
	{
		switch (Renderer::GetApi())
		{
		case OPENGL_API:
			return new OpenGL::ShaderProgram(vertexShader, fragmentShader);
		default:
			SL_ERROR("Starlight engine supports only OpenGL now");
			return nullptr;
		}
	}

	IShaderProgram* CreateProgram(const std::string& vertexShader, const std::string& geometryShader, const std::string& fragmentShader)
	{
		switch (Renderer::GetApi())
		{
		case OPENGL_API:
			return new OpenGL::ShaderProgram(vertexShader, geometryShader, fragmentShader);
		default:
			SL_ERROR("Starlight engine supports only OpenGL now");
			return nullptr;
		}
	}
}