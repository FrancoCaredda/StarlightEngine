#ifndef SHADER_H
#define SHADER_H

#include "defines.h"

#include "glm/glm.hpp"

#include <string>


namespace Starlight
{
	class STARLIGHT_API IShaderProgram
	{
	public:
		virtual bool Link() noexcept = 0;
		virtual void Bind() const noexcept = 0;
		virtual void Unbind() const noexcept = 0;

		virtual void SetUniformf(const std::string& name, float value) = 0;
		virtual void SetUniformVec2f(const std::string& name, const glm::vec2& vector) = 0;
		virtual void SetUniformVec3f(const std::string& name, const glm::vec3& vector) = 0;
		virtual void SetUniformi(const std::string& name, int value) = 0;

		virtual void SetUniformMat4f(const std::string& name, const glm::mat4& matrix) = 0;

		virtual ~IShaderProgram() = default;
	};

	STARLIGHT_API IShaderProgram* CreateProgram(const std::string & vertexShader, const std::string & fragmentShader);
	STARLIGHT_API IShaderProgram* CreateProgram(const std::string& vertexShader, const std::string& geometryShader, const std::string& fragmentShader);
}

#endif