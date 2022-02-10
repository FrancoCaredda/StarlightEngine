#include "AssetManager.h"

namespace Starlight
{
	AssetManager AssetManager::s_Instance;

	bool AssetManager::LoadTexture(Formats format, const std::string& filepath)
	{
		ITexture2D* texture = CreateTexture2D(format, filepath);

		if (texture == nullptr)
			return false;

		std::string name = FormatName(filepath);
		s_Instance.m_TextureTable.insert({ name, texture });
	
		return true;
	}
	
	bool AssetManager::HasTexture(const std::string& name)
	{
		return s_Instance.m_TextureTable.find(name) != s_Instance.m_TextureTable.end();
	}
	
	ITexture2D* AssetManager::GetTexture(const std::string& name)
	{
		if (HasTexture(name))
			return s_Instance.m_TextureTable[name];

		return nullptr;
	}

	bool AssetManager::LoadStaticMesh(const std::string& filepath)
	{
		Assimp::Importer importer;

		s_Instance.m_Scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_GenSmoothNormals |
			aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

		uint32_t position = filepath.find_last_of("/\\");
		s_Instance.m_NativePath = filepath.substr(0, position);

		std::string name = FormatName(filepath);
		s_Instance.m_StaticMeshTable.insert({ name, new StaticMesh() });

		if (s_Instance.m_Scene == nullptr)
		{
			SL_ERROR(importer.GetErrorString());
			return false;
		}

		s_Instance.ProcessScene(name, true);
		s_Instance.m_StaticMeshTable[name]->WriteData();

		return true;
	}

	bool AssetManager::HasStaticMesh(const std::string& name)
	{
		return s_Instance.m_StaticMeshTable.find(name) != s_Instance.m_StaticMeshTable.end();
	}

	StaticMesh* AssetManager::GetStaticMesh(const std::string& name)
	{
		if (HasStaticMesh(name))
			return s_Instance.m_StaticMeshTable[name];

		return nullptr;
	}
	
	AssetManager::~AssetManager()
	{
		for (auto i = s_Instance.m_TextureTable.begin();
			i != s_Instance.m_TextureTable.end(); i++)
		{
			delete i->second;
		}

		s_Instance.m_TextureTable.clear();
	}

	void AssetManager::ProcessScene(const std::string& key, bool staticMesh)
	{
		ProcessNode(m_Scene->mRootNode, key, staticMesh);
	}

	void AssetManager::ProcessNode(const aiNode* node, const std::string& key, bool staticMesh)
	{
		for (int i = 0; i < node->mNumMeshes; i++)
		{
			if (staticMesh)
			{
				ReadStaticMesh(m_Scene->mMeshes[node->mMeshes[i]],
					s_Instance.m_StaticMeshTable[key]);

				ReadStaticMaterial(m_Scene->mMeshes[node->mMeshes[0]],
					s_Instance.m_StaticMeshTable[key]);
			}
		}

		for (int i = 0; i < node->mNumChildren; i++)
			ProcessNode(node->mChildren[i], key, staticMesh);
	}

	void AssetManager::ReadStaticMesh(aiMesh* mesh, StaticMesh* outMesh)
	{
		static int last = 0;
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

		outMesh->InsertVertecies(vertecies);
	}

	void AssetManager::ReadStaticMaterial(aiMesh* mesh, StaticMesh* outMesh)
	{
		aiMaterial* material = m_Scene->mMaterials[mesh->mMaterialIndex];
		Material nativeMaterial;

		aiString path;
		std::string fullPath;
		std::string name;

		int diffuseCount = material->GetTextureCount(aiTextureType_DIFFUSE);
		int specularCount = material->GetTextureCount(aiTextureType_SPECULAR);

		for (int i = 0; i < diffuseCount; i++)
		{
			material->GetTexture(aiTextureType_DIFFUSE, i, &path);
			fullPath = m_NativePath + "/" + path.C_Str();

			name = AssetManager::FormatName(fullPath);

			if (AssetManager::HasTexture(name))
			{
				nativeMaterial.Diffuse.push_back(AssetManager::GetTexture(name));
			}
			else
			{
				AssetManager::LoadTexture(RGB, fullPath);
				nativeMaterial.Diffuse.push_back(AssetManager::GetTexture(name));
			}
		}

		for (int i = 0; i < specularCount; i++)
		{
			material->GetTexture(aiTextureType_SPECULAR, 0, &path);

			fullPath = m_NativePath + "/" + path.C_Str();

			name = AssetManager::FormatName(fullPath);

			if (AssetManager::HasTexture(name))
			{
				nativeMaterial.Specular.push_back(AssetManager::GetTexture(name));
			}
			else
			{
				AssetManager::LoadTexture(RGB, fullPath);
				nativeMaterial.Specular.push_back(AssetManager::GetTexture(name));
			}
		}

		outMesh->SetMaterial(nativeMaterial);
	}

	std::string AssetManager::FormatName(const std::string& filepath) noexcept
	{
		uint32_t firstPointPosition = filepath.find_first_of(".");
		uint32_t lastSlashPosition = filepath.find_last_of("\\/");

		char string[BUFFER_SIZE] = { 0 };

		filepath.copy(string, firstPointPosition - lastSlashPosition - 1, lastSlashPosition + 1);

		return std::string(string);
	}
}