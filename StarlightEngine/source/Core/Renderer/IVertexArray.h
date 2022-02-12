#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "defines.h"
#include "IBuffers.h"

#include "glm/glm.hpp"


namespace Starlight
{
	/// <summary>
	/// First component of std::pair is an index to attribute. 
	/// Second component of std::pair is an vector of uint32_t components.
	/// X component of vector defines elements count of this attribute.
	/// Y component of vector defines stride between two vertecies. (must be in bytes).
	/// Z component of vector defines offset to attribute (must be in bytes).
	/// </summary>
	typedef std::vector<std::pair<uint32_t, glm::uvec3>> VertexLayout;

	class STARLIGHT_API IVertexArray
	{
	public:
		virtual void Bind() const noexcept = 0;
		virtual void Unbind() const noexcept = 0;

		virtual void SetVertexLayout(const VertexLayout& layout) = 0;

		virtual void AttachVertexBuffer(IVertexBuffer* buffer) = 0;
		virtual void SetIndexBuffer(IIndexBuffer* buffer) = 0;

		virtual ~IVertexArray() = default;
	};

	STARLIGHT_API IVertexArray* CreateVertexArray() noexcept;
}
#endif // !VERTEX_ARRAY_H
