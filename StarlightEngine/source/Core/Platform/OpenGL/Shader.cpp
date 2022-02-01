#include "Shader.h"

#include "Core/Log.h"

#include "glm/gtc/type_ptr.hpp"

#include <fstream>

#ifdef SL_PLATFORM_WINDOWS
#include <Windows.h>

#define OPENGL_SHADER_ERROR(MSG) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);\
								 std::cerr << MSG << std::endl;\
								 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STD_COLOR)
#else
#define OPENGL_SHADER_ERROR(MSG) std::cerr << MSG << std::endl
#endif // SL_PLATFORM_WINDOWS

namespace Starlight
{
	namespace OpenGL
	{
		Shader::Shader(GLenum type)
		{
			m_Id = glCreateShader(type);
			SL_STD_EXCEPTION(m_Id == 0, "Shader isn\'t created!");
		}

		void Shader::Load(const std::string& filepath)
		{
			std::ifstream file(filepath);

			if (!file.is_open())
			{
				SL_ERROR(filepath + " doesn\'t exist");
				return;
			}

			std::string source = "";
			char Buffer[BUFFER_SIZE] = { 0 };

			while (file.good())
			{
				file.getline(Buffer, BUFFER_SIZE);
				
				source += Buffer;
				source += "\n";

				memset(Buffer, 0, BUFFER_SIZE);

				if (file.fail() || file.eof())
					break;
			}

#ifdef _DEBUG
			std::cout << source << std::endl;
#endif
			
			const char* internalSource = source.c_str();

			glShaderSource(m_Id, 1, &internalSource, nullptr);
		}

		bool Shader::Compile() noexcept
		{
			glCompileShader(m_Id);

			int status;
			glGetShaderiv(m_Id, GL_COMPILE_STATUS, &status);

			char Buffer[BUFFER_SIZE] = { 0 };

			if (status == GL_FALSE)
			{
				glGetShaderInfoLog(m_Id, BUFFER_SIZE, nullptr, Buffer);
				OPENGL_SHADER_ERROR(Buffer);

				return false;
			}

			return true;
		}

		Shader::~Shader()
		{
			glDeleteShader(m_Id);
		}

		ShaderProgram::ShaderProgram(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc)
		{
			m_Id = glCreateProgram();
			SL_STD_EXCEPTION(m_Id == 0, "Shader program isn\'t created!");

			Shader vertexShader(GL_VERTEX_SHADER);
			Shader fragmentShader(GL_FRAGMENT_SHADER);

			vertexShader.Load(vertexShaderSrc);
			fragmentShader.Load(fragmentShaderSrc);

			SL_STD_EXCEPTION(!vertexShader.Compile() || !fragmentShader.Compile(), "Shader isn\'t compiled!");

			glAttachShader(m_Id, vertexShader.m_Id);
			glAttachShader(m_Id, fragmentShader.m_Id);
		}

		ShaderProgram::ShaderProgram(const std::string& vertexShaderSrc, const std::string& geometryShaderSrc, const std::string& fragmentShaderSrc)
		{
			m_Id = glCreateProgram();
			SL_STD_EXCEPTION(m_Id == 0, "Shader program isn\'t created!");

			Shader vertexShader(GL_VERTEX_SHADER);
			Shader geometryShader(GL_GEOMETRY_SHADER);
			Shader fragmentShader(GL_FRAGMENT_SHADER);

			vertexShader.Load(vertexShaderSrc);
			geometryShader.Load(geometryShaderSrc);
			fragmentShader.Load(fragmentShaderSrc);

			SL_STD_EXCEPTION(!vertexShader.Compile() || !geometryShader.Compile() || !fragmentShader.Compile(), "Shader isn\'t compiled!");

			glAttachShader(m_Id, vertexShader.m_Id);
			glAttachShader(m_Id, geometryShader.m_Id);
			glAttachShader(m_Id, fragmentShader.m_Id);
		}

		bool ShaderProgram::Link() noexcept
		{
			glLinkProgram(m_Id);

			int status;
			glGetProgramiv(m_Id, GL_LINK_STATUS, &status);

			char Buffer[BUFFER_SIZE] = { 0 };

			if (status == GL_FALSE)
			{
				glGetProgramInfoLog(m_Id, BUFFER_SIZE, nullptr, Buffer);
				OPENGL_SHADER_ERROR(Buffer);

				return false;
			}
			
			glValidateProgram(m_Id);
			glGetProgramiv(m_Id, GL_VALIDATE_STATUS, &status);

			if (status == GL_FALSE)
			{
				glGetProgramInfoLog(m_Id, BUFFER_SIZE, nullptr, Buffer);
				OPENGL_SHADER_ERROR(Buffer);

				return false;
			}

			return true;
		}
		
		void ShaderProgram::Bind() const noexcept
		{
			glUseProgram(m_Id);
		}
		
		void ShaderProgram::Unbind() const noexcept
		{
			glUseProgram(0);
		}

		void ShaderProgram::SetUniformf(const std::string& name, float value)
		{
			if (GetUniformLocation(name))
				glUniform1f(m_Uniforms[name], value);
		}

		void ShaderProgram::SetUniformi(const std::string& name, int value)
		{
			if (GetUniformLocation(name))
				glUniform1i(m_Uniforms[name], value);
		}

		void ShaderProgram::SetUniformVec2f(const std::string& name, const glm::vec2& vector)
		{
			if (GetUniformLocation(name))
				glUniform2fv(m_Uniforms[name], 1, glm::value_ptr(vector));
		}

		void ShaderProgram::SetUniformVec3f(const std::string& name, const glm::vec3& vector)
		{
			if (GetUniformLocation(name))
				glUniform3fv(m_Uniforms[name], 1, glm::value_ptr(vector));
		}

		void ShaderProgram::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
		{
			if (GetUniformLocation(name))
				glUniformMatrix4fv(m_Uniforms[name], 1, GL_FALSE, glm::value_ptr(matrix));
		}

		bool ShaderProgram::GetUniformLocation(const std::string& name)
		{
			if (m_Uniforms.find(name) == m_Uniforms.end())
			{
				int location = glGetUniformLocation(m_Id, name.c_str());

				if (location == -1)
				{
					SL_WARN(name + " doesn\'t exist!");
					return false;
				}

				m_Uniforms.insert({ name, location });
			}

			return true;
		}

		ShaderProgram::~ShaderProgram()
		{
			glDeleteShader(m_Id);
		}
	}
}