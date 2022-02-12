#include "Buffers.h"

namespace Starlight
{
	namespace OpenGL
	{
		VertexBuffer::VertexBuffer(GLenum usage)
			: m_Usage(usage)
		{
			glCreateBuffers(1, &m_Id);
		}

		void VertexBuffer::Bind() const noexcept
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_Id);
		}

		void VertexBuffer::Unbind() const noexcept
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void VertexBuffer::Allocate(size_t size) noexcept
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_Id);
			glBufferData(GL_ARRAY_BUFFER, size, nullptr, m_Usage);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void VertexBuffer::Write(void* data, size_t size, size_t offset) noexcept
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_Id);
			glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void* VertexBuffer::Map() noexcept
		{
			return glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
		}

		void VertexBuffer::Unmap() noexcept
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
		}

		VertexBuffer::~VertexBuffer()
		{
			glDeleteBuffers(1, &m_Id);
		}

		IndexBuffer::IndexBuffer(GLenum usage)
			: m_Usage(usage)
		{
			glCreateBuffers(1, &m_Id);
		}

		void IndexBuffer::Bind() const noexcept
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
		}

		void IndexBuffer::Unbind() const noexcept
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		void IndexBuffer::Allocate(size_t size) noexcept
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, m_Usage);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		void IndexBuffer::Write(const std::vector<uint32_t>& data, size_t size, size_t offset) noexcept
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, (void*)data.data());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		
			m_Count += data.size();
		}

		void* IndexBuffer::Map() noexcept
		{
			return glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_WRITE);
		}

		void IndexBuffer::Unmap() noexcept
		{
			glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		}

		IndexBuffer::~IndexBuffer()
		{
			glDeleteBuffers(1, &m_Id);
		}

		UniformBuffer::UniformBuffer(GLenum usage)
			: m_Usage(usage)
		{
			glCreateBuffers(1, &m_Id);
		}
		
		void UniformBuffer::Bind() const noexcept
		{
			glBindBuffer(GL_UNIFORM_BUFFER, m_Id);
		}

		void UniformBuffer::Unbind() const noexcept
		{
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}
		
		void UniformBuffer::SetBinding(uint32_t binding)
		{
			m_Binding = binding;

			glBindBuffer(GL_UNIFORM_BUFFER, m_Id);
			glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_Id);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}
		
		void UniformBuffer::Allocate(size_t size) noexcept
		{
			glBindBuffer(GL_UNIFORM_BUFFER, m_Id);
			glBufferData(GL_UNIFORM_BUFFER, size, nullptr, m_Usage);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}
		
		void UniformBuffer::Write(void* data, size_t size, size_t offset) noexcept
		{
			glBindBuffer(GL_UNIFORM_BUFFER, m_Id);
			glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}
		
		void* UniformBuffer::Map() noexcept
		{
			return glMapBuffer(GL_UNIFORM_BUFFER, GL_READ_WRITE);
		}
		
		void UniformBuffer::Unmap() noexcept
		{
			glUnmapBuffer(GL_UNIFORM_BUFFER);
		}
		
		UniformBuffer::~UniformBuffer()
		{
			glDeleteBuffers(1, &m_Id);
		}
	}
}
