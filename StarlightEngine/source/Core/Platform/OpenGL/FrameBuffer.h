#ifndef OPENGL_FRAME_BUFFER_H
#define OPENGL_FRAME_BUFFER_H

#include "Core/Renderer/IFrameBuffer.h"

namespace Starlight
{
	namespace OpenGL
	{
		class RenderBuffer : public IRenderBuffer
		{
		public:
			RenderBuffer();

			virtual void Bind() const noexcept;
			virtual void Unbind() const noexcept;

			virtual void Allocate(Formats format, int width, int height) noexcept;

			virtual uint32_t GetNative() const noexcept;

			virtual ~RenderBuffer();

			friend class FrameBuffer;
		private:
			uint32_t m_Id;
		};


		class FrameBuffer : public IFrameBuffer
		{
		public:
			FrameBuffer();

			virtual void Bind() const noexcept;
			virtual void Unbind() const noexcept;

			virtual void AttachColorBuffer(Attachments attachment, ITexture2D* colorBuffer) noexcept;
			virtual void AttachRenderBuffer(Attachments attachment, IRenderBuffer* buffer) noexcept;

			virtual bool Check() const noexcept;

			virtual ~FrameBuffer();
		private:
			uint32_t m_Id;
		};
	}
}

#endif // !OPENGL_FRAME_BUFFER_H
