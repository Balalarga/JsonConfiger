#pragma once
#include <filesystem>
#include <map>
#include <memory>
#include <string>

namespace JC
{
class IJsonConfig;

struct ConfigMetadata
{
	std::shared_ptr<IJsonConfig> config;
	std::shared_ptr<IJsonConfig> diskConfig;
	bool bWasLoaded = false;
};

class ConfigManager
{
public:
	ConfigManager(const std::string& baseDirPath);
	~ConfigManager();
	
	template<class T, class ...TArgs>
	std::enable_if_t<std::derived_from<T, IJsonConfig>, ConfigMetadata> CreateConfig(TArgs&& ...args)
	{
		auto config = std::make_shared<T>(args...);
		config->_filepath = std::filesystem::path(_baseDirPath).append(config->_filepath).generic_string();
		
		bool bLoaded = LoadConfig(config);
		
		auto meta = ConfigMetadata{config, bLoaded ? std::make_shared<T>(*config) : nullptr, bLoaded};
		_configs[config->GetFilepath()] = meta;
		
		return meta;
	}

	const ConfigMetadata* GetMetadata(const std::shared_ptr<IJsonConfig>& config) const;
	
	bool LoadConfig(const std::shared_ptr<IJsonConfig>& config);
	bool SaveConfig(const ConfigMetadata* config);

private:
	const std::string& _baseDirPath;
	
	std::map<std::string, ConfigMetadata> _configs;
};
}
