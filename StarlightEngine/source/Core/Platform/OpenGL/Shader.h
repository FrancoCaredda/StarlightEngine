#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include "Core/Renderer/IShader.h"

#include <unordered_map>

namespace Starlight
{
	namespace OpenGL
	{
		class Shader
		{
		public:
			Shader(GLenum type);

			void Load(const std::string& filepath);
			bool Compile() noexcept;

			friend class ShaderProgram;

			~Shader();
		private:
			uint32_t m_Id;
		};

		class ShaderProgram : public IShaderProgram
		{
		public:
			ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
			ShaderProgram(const std::string& vertexShader, const std::string& geometryShader, const std::string& fragmentShader);

			virtual bool Link() noexcept override;
			virtual void Bind() const noexcept override;
			virtual void Unbind() const noexcept override;

			virtual void SetUniformf(const std::string& name, float value) override;
			virtual void SetUniformVec2f(const std::string& name, const glm::vec2& vector) override;
			virtual void SetUniformVec3f(const std::string& name, const glm::vec3& vector) override;
			virtual void SetUniformi(const std::string& name, int value) override;

			virtual void SetUniformMat4f(const std::string& name, const glm::mat4& matrix) override;

			virtual ~ShaderProgram();
		private:
			bool GetUniformLocation(const std::string& name);
		private:
			uint32_t m_Id;
			std::unordered_map<std::string, int> m_Uniforms;
		};
	}
}

#endif // !OPENGL_SHADER_H
