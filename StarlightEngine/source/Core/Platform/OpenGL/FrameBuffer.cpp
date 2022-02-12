#include "FrameBuffer.h"

namespace Starlight
{
	namespace OpenGL
	{
		RenderBuffer::RenderBuffer()
		{
			glCreateRenderbuffers(1, &m_Id);
		}

		void RenderBuffer::Bind() const noexcept
		{
			glBindRenderbuffer(GL_RENDERBUFFER, m_Id);
		}

		void RenderBuffer::Unbind() const noexcept
		{
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
		}
		
		void RenderBuffer::Allocate(Formats format, int width, int height) noexcept
		{
			glBindRenderbuffer(GL_RENDERBUFFER, m_Id);
			glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
		}
		
		RenderBuffer::~RenderBuffer()
		{
			glDeleteRenderbuffers(1, &m_Id);
		}
		
		uint32_t RenderBuffer::GetNative() const noexcept
		{
			return m_Id;
		}
		
		FrameBuffer::FrameBuffer()
		{
			glCreateFramebuffers(1, &m_Id);
		}
		
		void FrameBuffer::Bind() const noexcept
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_Id);
		}
		
		void FrameBuffer::Unbind() const noexcept
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		
		void FrameBuffer::AttachColorBuffer(Attachments attachment, ITexture2D* colorBuffer) noexcept
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_Id);
			glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, colorBuffer->GetId(), 0);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		
		void FrameBuffer::AttachRenderBuffer(Attachments attachment, IRenderBuffer* buffer) noexcept
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_Id);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, buffer->GetNative());
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		
		bool FrameBuffer::Check() const noexcept
		{
			return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
		}
		
		FrameBuffer::~FrameBuffer()
		{
			glDeleteFramebuffers(1, &m_Id);
		}
	}
}