#ifndef MODEL_H
#define MODEL_H

#include "defines.h"

#include "glm/glm.hpp"

#include "Core/Renderer/IBuffers.h"
#include "Core/Renderer/IVertexArray.h"

#include "Components/Graphics/Material.h"


namespace Starlight
{
	typedef struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normals;
		glm::vec2 TextureCoord;
	} Vertex;

	class STARLIGHT_API Mesh
	{
	public:
		Mesh();
		Mesh(const Mesh&) = delete;

		void SetVertecies(const std::vector<Vertex>& vertecies) noexcept;
		void SetIndecies(const std::vector<uint32_t>& indecies) noexcept;

		// Writes data to GPU buffers
		void WriteData() noexcept;

		inline const std::vector<Vertex>& GetVertecies() const noexcept { return m_Vertecies; }
		inline const std::vector<uint32_t>& GetIndecies() const noexcept { return m_Indecies; }

		inline IVertexBuffer* GetVertexBuffer() const noexcept { return m_VertexBuffer; }
		inline IIndexBuffer* GetIndexBuffer() const noexcept { return m_IndexBuffer; }
		inline IVertexArray* GetVertexArray() const noexcept { return m_VertexArray; }

		void Bind() const noexcept;
		void Unbind() const noexcept;

		~Mesh();
	private:
		std::vector<Vertex> m_Vertecies;
		std::vector<uint32_t> m_Indecies;

		IVertexBuffer* m_VertexBuffer = nullptr;
		IIndexBuffer* m_IndexBuffer = nullptr;
		IVertexArray* m_VertexArray = nullptr;
	};
}

#endif // !MODEL_H

