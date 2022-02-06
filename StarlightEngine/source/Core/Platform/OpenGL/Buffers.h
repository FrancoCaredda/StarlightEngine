#ifndef OPENGL_BUFFERS_H
#define OPENGL_BUFFERS_H

#include "Core/Renderer/IBuffers.h"

namespace Starlight
{
	namespace OpenGL
	{
		class VertexBuffer : public IVertexBuffer
		{
		public:
			VertexBuffer(GLenum usage);

			virtual void Bind() const noexcept override;
			virtual void Unbind() const noexcept override;

			// Allocates bunch of VRAM. Size in bytes
			virtual void Allocate(size_t size) noexcept override;

			// Writes data to allocated buffer. Size and offset in bytes
			virtual void Write(void* data, size_t size, size_t offset) noexcept override;

			virtual void* Map() noexcept override;
			virtual void Unmap() noexcept override;

			virtual ~VertexBuffer();
		private:
			uint32_t m_Id;
			uint32_t m_Count;

			GLenum m_Usage;
		};

		class IndexBuffer : public IIndexBuffer
		{
		public:
			IndexBuffer(GLenum usage);

			virtual void Bind() const noexcept override;
			virtual void Unbind() const noexcept override;

			// Allocates bunch of VRAM. Size in bytes
			virtual void Allocate(size_t size) noexcept override;

			// Writes data to allocated buffer. Size and offset in bytes
			virtual void Write(const std::vector<uint32_t>& data, size_t size, size_t offset) noexcept override;

			virtual void* Map() noexcept override;
			virtual void Unmap() noexcept override;

			inline uint32_t GetCount() const noexcept { 
				return m_Count; 
			}

			virtual ~IndexBuffer();
		private:
			uint32_t m_Id;
			uint32_t m_Count = 0;

			GLenum m_Usage;
		};
	}
}

#endif // !OPENGL_BUFFERS_H
