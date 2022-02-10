#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include "defines.h"
#include "enums.h"

#include "Core/Log.h"
#include "Core/Renderer/ITexture.h"
#include "Components/Mesh/Mesh.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

namespace Starlight
{
	class STARLIGHT_API AssetManager
	{
	public:
		SL_SINGLE_CLASS(AssetManager);

		static bool LoadTexture(Formats format, const std::string& filepath);
		static bool HasTexture(const std::string& name);
		static ITexture2D* GetTexture(const std::string& name);


		static bool LoadStaticMesh(const std::string& filepath);
		static bool HasStaticMesh(const std::string& name);
		static StaticMesh* GetStaticMesh(const std::string& name);

		static bool LoadDynamicMesh() { return false; }
		static bool HasDynamicMesh() { return false; }

		static std::string FormatName(const std::string& filepath) noexcept;

		~AssetManager();
	private:
		void ProcessScene(const std::string& key, bool staticMesh);
		void ProcessNode(const aiNode* node, const std::string& key, bool staticMesh);
		void ReadStaticMesh(aiMesh* mesh, StaticMesh* outMesh);
		void ReadStaticMaterial(aiMesh* mesh, StaticMesh* outMesh);
	private:
		AssetManager() = default;
		static AssetManager s_Instance;
		
		const aiScene* m_Scene;
		std::string m_NativePath;

		std::map<std::string, ITexture2D*> m_TextureTable;
		std::map<std::string, StaticMesh*> m_StaticMeshTable;
	};
}

#endif // !ASSET_MANAGER_H

