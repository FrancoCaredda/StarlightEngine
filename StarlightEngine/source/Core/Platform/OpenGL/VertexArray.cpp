#include "VertexArray.h"

namespace Starlight
{
	namespace OpenGL
	{
		VertexArray::VertexArray()
		{
			glCreateVertexArrays(1, &m_Id);
		}

		void VertexArray::Bind() const noexcept
		{
			m_IndexBuffer->Bind();
			m_VertexBuffers[0]->Bind();

			glBindVertexArray(m_Id);
		}

		void VertexArray::Unbind() const noexcept
		{
			m_IndexBuffer->Unbind();
			m_VertexBuffers[0]->Unbind();

			glBindVertexArray(0);
		}

		void VertexArray::SetVertexLayout(const VertexLayout& layout)
		{
			glBindVertexArray(m_Id);

			for (auto i = layout.begin(); i != layout.end(); i++)
				glVertexAttribPointer(i->first, i->second.x, GL_FLOAT, GL_FALSE, i->second.y, (const void*)i->second.z);

			for (auto i = layout.begin(); i != layout.end(); i++)
				glEnableVertexAttribArray(i->first);

			glBindVertexArray(0);
		}

		void VertexArray::AttachVertexBuffer(IVertexBuffer* buffer)
		{
			m_VertexBuffers.push_back(buffer);
		}

		void VertexArray::SetIndexBuffer(IIndexBuffer* indexBuffer)
		{
			m_IndexBuffer = indexBuffer;
		}

		VertexArray::~VertexArray()
		{
			glDeleteVertexArrays(1, &m_Id);
		}
	}
}