#include "Texture.h"

#include "Core/Log.h"
#include "stb_image.h"

namespace Starlight
{
	namespace OpenGL
	{
		Texture2D::Texture2D()
		{
			glGenTextures(1, &m_Id);
		}
		
		void Texture2D::Allocate(Formats format, int width, int height) noexcept
		{
			m_Size = { width, height };

			glBindTexture(GL_TEXTURE_2D, m_Id);
			glTexImage2D(GL_TEXTURE_2D, 0, format, m_Size.x, m_Size.y, 0, format, GL_UNSIGNED_BYTE, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

			glGenerateMipmap(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		bool Texture2D::Load(Formats format, const std::string& filepath) noexcept
		{
			int channels;

			stbi_set_flip_vertically_on_load(true);
			uint8_t* data = stbi_load(filepath.c_str(), (int*)&m_Size.x, (int*)&m_Size.y, &channels, 0);
			
			if (data == nullptr)
			{
				SL_WARN("No such file or directory. Please check your directory");
				return false;
			}

			glBindTexture(GL_TEXTURE_2D, m_Id);
			glTexImage2D(GL_TEXTURE_2D, 0, format, m_Size.x, m_Size.y, 0, format, GL_UNSIGNED_BYTE, data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

			glGenerateMipmap(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 0);

			m_Path = filepath;

			stbi_image_free(data);
			return true;
		}
		
		void Texture2D::Bind() const noexcept
		{
			glBindTexture(GL_TEXTURE_2D, m_Id);
		}
		
		void Texture2D::Unbind() const noexcept
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		
		void Texture2D::SetActiveSlot(int slot) noexcept
		{
			glActiveTexture(GL_TEXTURE0 + slot);
		}

		uint32_t Texture2D::GetId() const noexcept
		{
			return m_Id;
		}

		const std::string& Texture2D::GetPath() const noexcept
		{
			return m_Path;
		}
		
		Texture2D::~Texture2D()
		{
			glDeleteTextures(1, &m_Id);
		}
	}
}