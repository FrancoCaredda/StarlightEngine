#include "Model.h"

#include "glm/gtc/type_ptr.hpp"

#include "Core/Renderer/ITexture.h"
#include "Core/AssetManager.h"
#include "Core/Log.h"

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
			m_VertexBuffer->Write(glm::value_ptr(m_Vertecies[i].Normal),       sizeof(glm::vec3), offset + offsetof(Vertex, Normal));
			m_VertexBuffer->Write(glm::value_ptr(m_Vertecies[i].TextureCoord), sizeof(glm::vec2), offset + offsetof(Vertex, TextureCoord));

			offset += sizeof(Vertex);
		}

		m_IndexBuffer->Allocate(m_Indecies.size() * sizeof(uint32_t));
		m_IndexBuffer->Write(m_Indecies, m_Indecies.size() * sizeof(uint32_t), 0);
		
		m_VertexBuffer->Bind();
		m_IndexBuffer->Bind();

		m_VertexArray->SetVertexLayout({
			{0, {3, sizeof(Vertex), 0}},
			{1, {3, sizeof(Vertex), offsetof(Vertex, Normal)}},
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

	bool Model::Load(const std::string& filename) noexcept
	{
		Assimp::Importer importer;

		m_Scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_GenSmoothNormals | 
											  aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

		uint32_t position = filename.find_last_of("/\\");
		m_NativePath = filename.substr(0, position);

		if (m_Scene == nullptr)
		{
			SL_ERROR(importer.GetErrorString());
			return false;
		}

		ProcessScene();

		return true;
	}

	Model::~Model()
	{
		for (int i = 0; i < m_Meshes.size(); i++)
			delete m_Meshes[i];

		m_Meshes.clear();
	}

	void Model::ProcessScene()
	{
		ProcessNode(m_Scene->mRootNode);
	}

	void Model::ProcessNode(const aiNode* node)
	{
		for (int i = 0; i < node->mNumMeshes; i++)
		{
			m_Meshes.push_back(new Mesh());
			ReadSingleMesh(m_Scene->mMeshes[node->mMeshes[i]],
				m_Meshes[m_Meshes.size() - 1]);

			ReadSingleMaterial(m_Scene->mMeshes[node->mMeshes[0]], 
				m_Meshes[m_Meshes.size() - 1]);
		}

		for (int i = 0; i < node->mNumChildren; i++)
			ProcessNode(node->mChildren[i]);
	}

	void Model::ReadSingleMesh(aiMesh* mesh, Mesh* outMesh)
	{
		std::vector<Vertex> vertecies(mesh->mNumVertices);
		std::vector<uint32_t> indecies;

		glm::vec3 temp(0);

		for (int i = 0; i < mesh->mNumVertices; i++)
		{
			if (mesh->HasPositions())
			{
				temp.x = mesh->mVertices[i].x;
				temp.y = mesh->mVertices[i].y;
				temp.z = mesh->mVertices[i].z;

				vertecies[i].Position = temp;
			}

			if (mesh->HasNormals())
			{
				temp.x = mesh->mNormals[i].x;
				temp.y = mesh->mNormals[i].y;
				temp.z = mesh->mNormals[i].z;

				vertecies[i].Normal = temp;
			}

			if (mesh->mTextureCoords[0])
			{
				temp.x = mesh->mTextureCoords[0][i].x;
				temp.y = mesh->mTextureCoords[0][i].y;

				vertecies[i].TextureCoord = { temp.x, temp.y };
			}
		}

		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];

			for (int j = 0; j < face.mNumIndices; j++)
				indecies.push_back(face.mIndices[j]);
		}

		outMesh->SetVertecies(vertecies);
		outMesh->SetIndecies(indecies);
		outMesh->WriteData();
	}

	void Model::ReadSingleMaterial(aiMesh* mesh, Mesh* outMesh)
	{
		aiMaterial* material = m_Scene->mMaterials[mesh->mMaterialIndex];

		aiString path;
		std::string fullPath;
		std::string name;

		int diffuseCount = material->GetTextureCount(aiTextureType_DIFFUSE);
		int specularCount = material->GetTextureCount(aiTextureType_SPECULAR);

		outMesh->m_Material = new Material;

		for (int i = 0; i < diffuseCount; i++)
		{
			material->GetTexture(aiTextureType_DIFFUSE, i, &path);
			fullPath = m_NativePath + "/" + path.C_Str();

			name = AssetManager::FormatName(fullPath);

			if (AssetManager::HasTexture(name))
			{
				outMesh->m_Material->Diffuse.push_back(AssetManager::GetTexture(name));
			}
			else
			{
				AssetManager::LoadTexture(RGB, fullPath);
				outMesh->m_Material->Diffuse.push_back(AssetManager::GetTexture(name));
			}
		}

		for (int i = 0; i < specularCount; i++)
		{
			material->GetTexture(aiTextureType_SPECULAR, 0, &path);

			fullPath = m_NativePath + "/" + path.C_Str();

			name = AssetManager::FormatName(fullPath);

			if (AssetManager::HasTexture(name))
			{
				outMesh->m_Material->Specular.push_back(AssetManager::GetTexture(name));
			}
			else
			{
				AssetManager::LoadTexture(RGB, fullPath);
				outMesh->m_Material->Specular.push_back(AssetManager::GetTexture(name));
			}
		}
	}
}
