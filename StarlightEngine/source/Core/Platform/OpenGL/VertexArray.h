#ifndef OPENGL_VERTEX_ARRAY_H
#define OPENGL_VERTEX_ARRAY_H

#include "defines.h"
#include "Core/Renderer/IVertexArray.h"

#include <vector>

namespace Starlight
{
	namespace OpenGL
	{
		class VertexArray : public IVertexArray
		{
		public:
			VertexArray();

			virtual void Bind() const noexcept override;
			virtual void Unbind() const noexcept override;

			virtual void SetVertexLayout(const VertexLayout& layout) override;

			virtual void AttachVertexBuffer(IVertexBuffer* buffer) override;
			virtual void SetIndexBuffer(IIndexBuffer* buffer) override;

			virtual ~VertexArray();
		private:
			uint32_t m_Id;
			
			std::vector<IVertexBuffer*> m_VertexBuffers;
			IIndexBuffer* m_IndexBuffer = nullptr;
		};
	}
}

#endif // !OPENGL_VERTEX_ARRAY_H
