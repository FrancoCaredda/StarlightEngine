#ifndef TEXTURE_H
#define TEXTURE_H

#include "defines.h"

#include "Core/enums.h"

namespace Starlight
{
	class STARLIGHT_API ITexture2D
	{
	public:
		virtual void Allocate(Formats format, int width, int height) noexcept = 0;
		virtual bool Load(Formats format, const std::string& filepath) noexcept = 0;

		virtual void Bind() const noexcept = 0;
		virtual void Unbind() const noexcept = 0;

		// max slots available 31
		virtual void SetActiveSlot(int slot) noexcept = 0;
		virtual uint32_t GetId() const noexcept = 0;

		virtual const std::string& GetPath() const noexcept = 0;

		virtual ~ITexture2D() = default;

		friend class IFrameBuffer;
	};

	STARLIGHT_API ITexture2D* CreateTexture2D(Formats format, int width, int height);
	STARLIGHT_API ITexture2D* CreateTexture2D(Formats format, const std::string& filepath);
}

#endif // !TEXTURE_H
