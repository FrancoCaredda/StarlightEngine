#include "ShaderLibrary.h"

#include "Core/Log.h"

namespace Starlight
{
	ShaderLibrary ShaderLibrary::s_Instance;

	bool ShaderLibrary::CreateShaderProgram(const std::string& shaderName, const std::string& vertexShader, const std::string& fragmentShader)
	{
		try
		{
			IShaderProgram* program = CreateProgram(vertexShader, fragmentShader);
				
			if (!program->Link())
				return false;

			s_Instance.m_ShaderPrograms.insert({ shaderName, program });
		}
		catch (std::exception& e)
		{
			SL_ERROR(e.what());
			return false;
		}

		return true;
	}

	bool ShaderLibrary::CreateShaderProgram(const std::string& shaderName, const std::string& vertexShader, const std::string& geometryShader, const std::string& fragmentShader)
	{
		try
		{
			IShaderProgram* program = CreateProgram(vertexShader, geometryShader, fragmentShader);

			if (!program->Link())
				return false;

			s_Instance.m_ShaderPrograms.insert({ shaderName, program });
		}
		catch (std::exception& e)
		{
			SL_ERROR(e.what());
			return false;
		}

		return true;
	}
	
	void ShaderLibrary::AttachShaderProgram(const std::string& name, IShaderProgram* program)
	{
		if (s_Instance.m_ShaderPrograms.find(name) != s_Instance.m_ShaderPrograms.end())
		{
			SL_WARN("Shader program with name: " + name + " alredy exists! Please rename program");
			return;
		}

		s_Instance.m_ShaderPrograms.insert({ name, program });
	}
	
	IShaderProgram* ShaderLibrary::GetShaderProgram(const std::string& name) noexcept
	{
		if (s_Instance.m_ShaderPrograms.find(name) == s_Instance.m_ShaderPrograms.end())
			return nullptr;

		return s_Instance.m_ShaderPrograms[name];
	}
	
	ShaderLibrary::~ShaderLibrary()
	{
		for (auto i = s_Instance.m_ShaderPrograms.begin(); i != s_Instance.m_ShaderPrograms.end(); i++)
			delete i->second;
	}
}