#ifndef SHADER_LIBRARY_H
#define SHADER_LIBRARY_H

#include "defines.h"

#include "IShader.h"

namespace Starlight
{
	class STARLIGHT_API ShaderLibrary
	{
	public:
		SL_SINGLE_CLASS(ShaderLibrary);

		static bool CreateShaderProgram(const std::string shaderName, const std::string& vertexShader, const std::string& fragmentShader);
		static bool CreateShaderProgram(const std::string shaderName, const std::string& vertexShader, 
										const std::string& geometryShader, const std::string& fragmentShader);

		static void AttachShaderProgram(const std::string& name, IShaderProgram* program);
		static IShaderProgram* GetShaderProgram(const std::string& name) noexcept;

		~ShaderLibrary();
	private:
		ShaderLibrary() = default;
		static ShaderLibrary s_Instance;

		std::unordered_map<std::string, IShaderProgram*> m_ShaderPrograms;
	};
}
#endif // !SHADER_LIBRARY_H
