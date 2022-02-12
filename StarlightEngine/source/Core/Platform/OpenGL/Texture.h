#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

#include "defines.h"
#include "Core/Renderer/ITexture.h"
#include "glm/glm.hpp"

namespace Starlight
{
	namespace OpenGL
	{
		class Texture2D : public ITexture2D
		{
		public:
			Texture2D();

			virtual void Allocate(Formats format, int width, int height) noexcept override;
			virtual bool Load(Formats format, const std::string& filepath) noexcept override;

			virtual void Bind() const noexcept override;
			virtual void Unbind() const noexcept override;

			virtual void SetActiveSlot(int slot) noexcept override;
			virtual uint32_t GetId() const noexcept override;

			virtual const std::string& GetPath() const noexcept override;
			
			virtual ~Texture2D();
		private:
			uint32_t m_Id;
			uint32_t m_Slot;

			std::string m_Path;
		
			glm::uvec2 m_Size;
		};
	}
}

#endif // !OPENGL_TEXTURE_H
