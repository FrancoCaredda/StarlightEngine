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
			if (m_IndexBuffer != nullptr)
				m_IndexBuffer->Bind();
			
			m_VertexBuffers[0]->Bind();

			glBindVertexArray(m_Id);
		}

		void VertexArray::Unbind() const noexcept
		{
			if (m_IndexBuffer != nullptr)
				m_IndexBuffer->Unbind();

			m_VertexBuffers[0]->Unbind();

			glBindVertexArray(0);
		}

		void VertexArray::SetVertexLayout(const VertexLayout& layout)
		{
			glBindVertexArray(m_Id);

			for (int i = 0; i < layout.size(); i++)
				glVertexAttribPointer(layout[i].first, layout[i].second.x, GL_FLOAT, GL_FALSE, layout[i].second.y, (const void*)layout[i].second.z);

			for (int i = 0; i < layout.size(); i++)
				glEnableVertexAttribArray(layout[i].first);

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