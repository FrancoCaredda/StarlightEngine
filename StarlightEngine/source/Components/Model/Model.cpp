#include "Model.h"


#include "glm/gtc/type_ptr.hpp"

namespace Starlight
{
	Mesh::Mesh()
	{
		m_VertexArray = CreateVertexArray();
		m_VertexBuffer = CreateVertexBuffer();
		m_IndexBuffer = CreateIndexBuffer();
	}

	void Mesh::SetVertecies(const std::vector<Vertex>& vertecies) noexcept
	{
		m_Vertecies = vertecies;
	}
	
	void Mesh::SetIndecies(const std::vector<uint32_t>& indecies) noexcept
	{
		m_Indecies = indecies;
	}
	
	void Mesh::WriteData() noexcept
	{
		m_VertexBuffer->Allocate(sizeof(Vertex) * m_Vertecies.size());

		size_t offset = 0;

		for (int i = 0; i < m_Vertecies.size(); i++)
		{
			m_VertexBuffer->Write(glm::value_ptr(m_Vertecies[i].Position),     sizeof(glm::vec3), offset);
			m_VertexBuffer->Write(glm::value_ptr(m_Vertecies[i].Normals),      sizeof(glm::vec3), offset + offsetof(Vertex, Normals));
			m_VertexBuffer->Write(glm::value_ptr(m_Vertecies[i].TextureCoord), sizeof(glm::vec2), offset + offsetof(Vertex, TextureCoord));

			offset += sizeof(Vertex);
		}

		m_IndexBuffer->Allocate(m_Indecies.size() * sizeof(uint32_t));
		m_IndexBuffer->Write(m_Indecies, m_Indecies.size() * sizeof(uint32_t), 0);
		
		m_VertexBuffer->Bind();
		m_IndexBuffer->Bind();

		m_VertexArray->SetVertexLayout({
			{0, {3, sizeof(Vertex), 0}},
			{1, {3, sizeof(Vertex), offsetof(Vertex, Normals)}},
			{2, {2, sizeof(Vertex), offsetof(Vertex, TextureCoord)}}
		});

		m_VertexArray->AttachVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_VertexArray->Unbind();
	}
	
	void Mesh::Bind() const noexcept
	{
		m_VertexArray->Bind();
	}

	void Mesh::Unbind() const noexcept
	{
		m_VertexArray->Unbind();
	}

	Mesh::~Mesh()
	{
		delete m_VertexArray;
		delete m_VertexBuffer;
		delete m_IndexBuffer;
	}
}
