#include "AssetManager.h"

#ifdef _WIN32
#include "Platform/Windows/WinThread.h"
#else
#error Starlight supports only Windows now
#endif // _WIN32


#ifdef _WIN32
typedef struct Params
{
	std::vector<Starlight::Vertex>* Vertecies;
	aiMesh* Mesh;
} Params;

DWORD PLATFORM_API ReadPositions(void* params);
DWORD PLATFORM_API ReadNormals(void* params);
DWORD PLATFORM_API ReadTextureCoords(void* params);
#else
#error Starlight supports only Windows now
#endif // _WIN32


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

	bool AssetManager::LoadDynamicMesh(const std::string& filepath)
	{
		Assimp::Importer importer;

		s_Instance.m_Scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_GenSmoothNormals |
			aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

		uint32_t position = filepath.find_last_of("/\\");
		s_Instance.m_NativePath = filepath.substr(0, position);

		std::string name = FormatName(filepath);
		s_Instance.m_DynamicMeshTable.insert({ name, new DynamicMesh() });

		if (s_Instance.m_Scene == nullptr)
		{
			SL_ERROR(importer.GetErrorString());
			return false;
		}

		s_Instance.ProcessScene(name, false);
		s_Instance.m_DynamicMeshTable[name]->Sort();

		return true;
	}

	bool AssetManager::HasDynamicMesh(const std::string& name)
	{
		return s_Instance.m_DynamicMeshTable.find(name) != s_Instance.m_DynamicMeshTable.end();
	}

	DynamicMesh* AssetManager::GetDynamicMesh(const std::string& name)
	{
		if (HasDynamicMesh(name))
			return s_Instance.m_DynamicMeshTable[name];

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

				ReadStaticMaterial(m_Scene->mMeshes[node->mMeshes[i]],
					s_Instance.m_StaticMeshTable[key]);
			}
			else
			{
				StaticMesh* mesh = new StaticMesh(true);

				ReadDynamicMesh(m_Scene->mMeshes[node->mMeshes[i]],
					mesh);

				ReadStaticMaterial(m_Scene->mMeshes[node->mMeshes[i]],
					mesh);

				s_Instance.m_DynamicMeshTable[key]->AttachStaticMesh(mesh);
			}
		}

		for (int i = 0; i < node->mNumChildren; i++)
			ProcessNode(node->mChildren[i], key, staticMesh);
	}

	void AssetManager::ReadStaticMesh(aiMesh* mesh, StaticMesh* outMesh)
	{
		std::vector<Vertex> vertecies(mesh->mNumVertices);

#ifdef _WIN32
		Params params;
		params.Mesh = mesh;
		params.Vertecies = &vertecies;

		Windows::WinThread readPositions(ReadPositions, (void*)&params, nullptr);
		Windows::WinThread readNormals(ReadNormals, (void*)&params, nullptr);
		Windows::WinThread readTextureCoords(ReadTextureCoords, (void*)&params, nullptr);

		readPositions.WaitTillEnd();
		readNormals.WaitTillEnd();
		readTextureCoords.WaitTillEnd();
#else
#error Starlight supports only Windows now
#endif // _WIN32

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

	void AssetManager::ReadDynamicMesh(aiMesh* mesh, StaticMesh* outMember)
	{
		std::vector<Vertex> vertecies(mesh->mNumVertices);
		std::vector<uint32_t> indecies;

#ifdef _WIN32
		Params params;
		params.Mesh = mesh;
		params.Vertecies = &vertecies;

		Windows::WinThread readPositions(ReadPositions, (void*)&params, nullptr);
		Windows::WinThread readNormals(ReadNormals, (void*)&params, nullptr);
		Windows::WinThread readTextureCoords(ReadTextureCoords, (void*)&params, nullptr);

		readPositions.WaitTillEnd();
		readNormals.WaitTillEnd();
		readTextureCoords.WaitTillEnd();
#else
#error Starlight supports only Windows now
#endif // _WIN32

		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];

			for (int j = 0; j < face.mNumIndices; j++)
				indecies.push_back(face.mIndices[j]);
		}

		outMember->InsertVertecies(vertecies);
		outMember->InsertIndecies(indecies);

		outMember->WriteData();
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


#ifdef _WIN32
DWORD PLATFORM_API ReadPositions(void* params)
{
	Params* p = (Params*)params;

	glm::vec3 temp(0);
	std::vector<Starlight::Vertex>* vertecies = p->Vertecies;

	for (int i = 0; i < p->Mesh->mNumVertices; i++)
	{
		if (p->Mesh->HasPositions())
		{
			temp.x = p->Mesh->mVertices[i].x;
			temp.y = p->Mesh->mVertices[i].y;
			temp.z = p->Mesh->mVertices[i].z;

			(*vertecies)[i].Position = temp;
		}
	}

	return 0;
}

DWORD PLATFORM_API ReadNormals(void* params)
{
	Params* p = (Params*)params;

	glm::vec3 temp(0);
	std::vector<Starlight::Vertex>* vertecies = p->Vertecies;

	for (int i = 0; i < p->Mesh->mNumVertices; i++)
	{
		if (p->Mesh->HasNormals())
		{
			temp.x = p->Mesh->mNormals[i].x;
			temp.y = p->Mesh->mNormals[i].y;
			temp.z = p->Mesh->mNormals[i].z;

			(*vertecies)[i].Normal = temp;
		}
	}

	return 0;
}

DWORD PLATFORM_API ReadTextureCoords(void* params)
{
	Params* p = (Params*)params;

	glm::vec2 temp(0);
	std::vector<Starlight::Vertex>* vertecies = p->Vertecies;

	for (int i = 0; i < p->Mesh->mNumVertices; i++)
	{
		if (p->Mesh->mTextureCoords[0])
		{
			temp.x = p->Mesh->mTextureCoords[0][i].x;
			temp.y = p->Mesh->mTextureCoords[0][i].y;

			
			(*vertecies)[i].TextureCoord = temp;
		}
	}

	return 0;
}
#else
#error Starlight supports only Windows now
#endif // _WIN32
