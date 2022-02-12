#ifndef MESH_H
#define MESH_H

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
		glm::vec3 Normal;
		glm::vec2 TextureCoord;
	} Vertex;

	class STARLIGHT_API StaticMesh
	{
	public:
		StaticMesh(bool includeIndecies = 0);

		void InsertVertecies(const std::vector<Vertex>& vertecies) noexcept;
		void InsertIndecies(const std::vector<uint32_t>& indecies) noexcept;

		// Writes data to GPU buffers
		void WriteData() noexcept;
		inline bool IsWritten() const noexcept { return m_Written; }

		void SetMaterial(const Material& material) noexcept;
		inline const Material& GetMaterial() const noexcept { return m_Material; }

		inline int GetVerteciesCount() const noexcept { return m_Vertecies.size(); }
		inline int GetIndeciesCount() const noexcept { return (m_IncludeIndecies) ? m_Indecies.size() : 0; }

		friend class Renderer;
		~StaticMesh();
	private:
		void Bind() const noexcept;
		void Unbind() const noexcept;
	private:
		std::vector<Vertex> m_Vertecies;
		std::vector<uint32_t> m_Indecies;

		Material m_Material;

		bool m_Written = false;
		bool m_IncludeIndecies = 0;

		IVertexBuffer* m_VertexBuffer = nullptr;
		IIndexBuffer* m_IndexBuffer = nullptr;
		IVertexArray* m_VertexArray = nullptr;
	};

	class STARLIGHT_API DynamicMesh
	{
	public:
		DynamicMesh() = default;

		// Writes data to GPU buffers
		void WriteData() noexcept;

		void AttachStaticMesh(StaticMesh* mesh) noexcept;
		void Sort() noexcept;

		inline uint32_t GetCount() const noexcept { return m_Meshes.size(); }
		inline StaticMesh* operator[](uint32_t index) { return (index >= m_Meshes.size()) ? nullptr : m_Meshes[index]; }

		~DynamicMesh();
	private:
		std::vector<StaticMesh*> m_Meshes;
	};
}

#endif // !MESH_H

