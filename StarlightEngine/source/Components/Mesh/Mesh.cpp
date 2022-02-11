#include "Mesh.h"

#include "glm/gtc/type_ptr.hpp"

#include "Core/Renderer/ITexture.h"
#include "Core/AssetManager.h"
#include "Core/Log.h"

#include <algorithm>

namespace Starlight
{
	StaticMesh::StaticMesh(bool includeIndecies)
	{
		m_VertexArray = CreateVertexArray();
		m_VertexBuffer = CreateVertexBuffer();

		if (includeIndecies)
			m_IndexBuffer = CreateIndexBuffer();

		m_IncludeIndecies = includeIndecies;
	}

	void StaticMesh::InsertVertecies(const std::vector<Vertex>& vertecies) noexcept
	{
		m_Vertecies.insert(m_Vertecies.end(), vertecies.begin(), vertecies.end());
	}
	
	void StaticMesh::InsertIndecies(const std::vector<uint32_t>& indecies) noexcept
	{
		if (m_IncludeIndecies)
			m_Indecies.insert(m_Indecies.end(), indecies.begin(), indecies.end());
	}
	
	void StaticMesh::WriteData() noexcept
	{
		m_VertexBuffer->Allocate(sizeof(Vertex) * m_Vertecies.size());

		size_t offset = 0;

		for (int i = 0; i < m_Vertecies.size(); i++)
		{
			m_VertexBuffer->Write(glm::value_ptr(m_Vertecies[i].Position),     sizeof(glm::vec3), offset);
			m_VertexBuffer->Write(glm::value_ptr(m_Vertecies[i].Normal),       sizeof(glm::vec3), offset + offsetof(Vertex, Normal));
			m_VertexBuffer->Write(glm::value_ptr(m_Vertecies[i].TextureCoord), sizeof(glm::vec2), offset + offsetof(Vertex, TextureCoord));

			offset += sizeof(Vertex);
		}

		m_VertexBuffer->Bind();

		if (m_IncludeIndecies)
		{
			m_IndexBuffer->Allocate(m_Indecies.size() * sizeof(uint32_t));
			m_IndexBuffer->Write(m_Indecies, m_Indecies.size() * sizeof(uint32_t), 0);
			m_IndexBuffer->Bind();
		}

		m_VertexArray->SetVertexLayout({
			{0, {3, sizeof(Vertex), 0}},
			{1, {3, sizeof(Vertex), offsetof(Vertex, Normal)}},
			{2, {2, sizeof(Vertex), offsetof(Vertex, TextureCoord)}}
		});

		m_VertexArray->AttachVertexBuffer(m_VertexBuffer);

		if (m_IncludeIndecies)
			m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_VertexArray->Unbind();

		m_Written = true;
	}
	
	void StaticMesh::SetMaterial(const Material& material) noexcept
	{
		m_Material = material;
	}

	void StaticMesh::Bind() const noexcept
	{
		m_VertexArray->Bind();
	}

	void StaticMesh::Unbind() const noexcept
	{
		m_VertexArray->Unbind();
	}

	StaticMesh::~StaticMesh()
	{
		delete m_VertexArray;
		delete m_VertexBuffer;

		if (m_IncludeIndecies)
			delete m_IndexBuffer;
	}
	
	void DynamicMesh::WriteData() noexcept
	{
		for (int i = 0; i < m_Meshes.size(); i++)
			m_Meshes[i]->WriteData();
	}

	void DynamicMesh::AttachStaticMesh(StaticMesh* mesh) noexcept
	{
		m_Meshes.push_back(mesh);
	}

	void DynamicMesh::Sort() noexcept
	{
		std::sort(m_Meshes.begin(), m_Meshes.end(), [](StaticMesh* a, StaticMesh* b) {
			return a->GetVerteciesCount() < b->GetVerteciesCount();
		});
	}
	
	DynamicMesh::~DynamicMesh()
	{
		for (int i = 0; i < m_Meshes.size(); i++)
			delete m_Meshes[i];
	}
}
