#ifndef BUFFERS_H
#define BUFFERS_H

#include "defines.h"

#include "Core/Memory/Allocator.h"

namespace Starlight
{
	class STARLIGHT_API IVertexBuffer
	{
	public:	
		virtual void Bind() const noexcept = 0;
		virtual void Unbind() const noexcept = 0;

		virtual void Allocate(size_t size) noexcept = 0;

		// Writes data to allocated buffer. Size and offset in bytes
		virtual void Write(void* data, size_t size, size_t offset) noexcept = 0;

		virtual void* Map() noexcept = 0;
		virtual void Unmap() noexcept = 0;

		virtual ~IVertexBuffer() = default;
	};

	class STARLIGHT_API IIndexBuffer
	{
	public:
		virtual void Bind() const noexcept = 0;
		virtual void Unbind() const noexcept = 0;

		virtual void Allocate(size_t size) noexcept = 0;

		// Writes data to allocated buffer. Size and offset in bytes
		virtual void Write(const std::vector<uint32_t>& data, size_t size, size_t offset) noexcept = 0;

		virtual void* Map() noexcept = 0;
		virtual void Unmap() noexcept = 0;

		virtual ~IIndexBuffer() = default;
	};

	class STARLIGHT_API IUniformBuffer
	{
	public:		
		virtual void Bind() const noexcept = 0;
		virtual void Unbind() const noexcept = 0;
		
		virtual void SetBinding(uint32_t) = 0;

		virtual void Allocate(size_t size) noexcept = 0;

		// Writes data to allocated buffer. Size and offset in bytes
		virtual void Write(void* data, size_t size, size_t offset) noexcept = 0;

		virtual void* Map() noexcept = 0;
		virtual void Unmap() noexcept = 0;

		virtual ~IUniformBuffer() = default;
	};

	STARLIGHT_API IVertexBuffer* CreateVertexBuffer() noexcept;
	STARLIGHT_API IIndexBuffer* CreateIndexBuffer() noexcept;
	STARLIGHT_API IUniformBuffer* CreateUniformBuffer() noexcept;
}

#endif // !BUFFERS_H

