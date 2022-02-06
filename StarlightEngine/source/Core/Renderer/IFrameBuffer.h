#ifndef IFRAME_BUFFER_H
#define IFRAME_BUFFER_H

#include "defines.h"
#include "Core/enums.h"

#include "ITexture.h"

namespace Starlight
{
	class STARLIGHT_API IRenderBuffer
	{
	public:
		virtual void Bind() const noexcept = 0;
		virtual void Unbind() const noexcept = 0;

		virtual void Allocate(Formats format, int width, int heigth) noexcept = 0;
		
		virtual uint32_t GetNative() const noexcept = 0;

		virtual ~IRenderBuffer() = default;
	};

	STARLIGHT_API IRenderBuffer* CreateRenderBuffer(Formats format, int width, int height);

	class STARLIGHT_API IFrameBuffer
	{
	public:
		virtual void Bind() const noexcept = 0;
		virtual void Unbind() const noexcept = 0;

		virtual void AttachColorBuffer(Attachments attachment, ITexture2D* colorBuffer) noexcept = 0;
		virtual void AttachRenderBuffer(Attachments attachment, IRenderBuffer* colorBuffer) noexcept = 0;

		virtual bool Check() const noexcept = 0;

		virtual ~IFrameBuffer() = default;
	};

	STARLIGHT_API IFrameBuffer* CreateFrameBuffer();
}

#endif // !IFRAME_BUFFER_H