#include "ConfigManager.h"

#include "JsonConfiger/Archive/JsonArchive.h"
#include "IJsonConfig.h"

namespace JC
{
ConfigManager::ConfigManager(const std::string& baseDirPath):
	_baseDirPath(baseDirPath)
{
}

ConfigManager::~ConfigManager()
{
	for (ConfigMetadata& meta : _configs | std::views::values)
		SaveConfig(&meta);
}

const ConfigMetadata* ConfigManager::GetMetadata(const std::shared_ptr<IJsonConfig>& config) const
{
	if (!config)
		return nullptr;
	
	auto it = _configs.find(config->GetFilepath());
	if (it != _configs.end())
		return &it->second;

	return nullptr;
}

bool ConfigManager::LoadConfig(const std::shared_ptr<IJsonConfig>& config)
{
	if (!config)
		return false;
	
	JsonArchive serializer(config->GetFilepath(), ArchiveMode::Read);
	if (serializer.Open())
	{
		config->Serialize(&serializer);
		return true;
	}
	
	return false;
}

bool ConfigManager::SaveConfig(const ConfigMetadata* meta)
{
	if (!meta || !meta->config)
		return false;
	
	if (meta->config->Equals(meta->diskConfig.get()))
		return true;
	
	std::filesystem::path path(meta->config->GetFilepath());
	if (path.has_parent_path() && !exists(path.parent_path()))
		create_directories(path.parent_path());
	
	JsonArchive serializer(meta->config->GetFilepath(), ArchiveMode::Write);
	if (serializer.Open())
	{
		meta->config->Serialize(&serializer);
		*meta->diskConfig = *meta->config;
		return true;
	}
	
	return false;
}
}
