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
	
	AssetManager::~AssetManager()
	{
		for (auto i = s_Instance.m_TextureTable.begin();
			i != s_Instance.m_TextureTable.end(); i++)
		{
			delete i->second;
		}

		s_Instance.m_TextureTable.clear();
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