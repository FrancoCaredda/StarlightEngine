#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include "defines.h"
#include "enums.h"
#include "Core/Renderer/ITexture.h"

namespace Starlight
{
	class STARLIGHT_API AssetManager
	{
	public:
		SL_SINGLE_CLASS(AssetManager);

		static bool LoadTexture(Formats format, const std::string& filepath);
		static bool HasTexture(const std::string& name);
		static ITexture2D* GetTexture(const std::string& name);

		static std::string FormatName(const std::string& filepath) noexcept;

		~AssetManager();
	private:
		AssetManager() = default;
		static AssetManager s_Instance;
		
		std::unordered_map<std::string, ITexture2D*> m_TextureTable;
	};
}

#endif // !ASSET_MANAGER_H

