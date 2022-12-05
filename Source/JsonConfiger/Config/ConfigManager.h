#pragma once
#include <cassert>
#include <map>
#include <memory>
#include <string>
#include "IConfig.h"

namespace JC
{
class ConfigManager
{
	friend class IConfig;
public:
	~ConfigManager() = default;

	template<class T, class ...TArgs>
	std::enable_if_t<std::derived_from<T, IConfig>, std::shared_ptr<T>> CreateConfigs(TArgs&& ...args)
	{
		ConfigData configData;
		configData.userConfig = std::make_shared<T>(args...);
		configData.defaultConfig = std::make_shared<T>(args...);
		assert(!_configs.contains(configData.defaultConfig->GetFilepath()));
		
		_configs[configData.defaultConfig->GetFilepath()] = configData;
		
		LoadConfig(configData);
		if (configData.defaultConfig->IsDefaultOnly())
			return std::static_pointer_cast<T>(configData.defaultConfig);
		return std::static_pointer_cast<T>(configData.userConfig);
	}
	
	static std::string GetConfigDir();
	static std::string GetDefaultConfigDir();
	
	void SaveAll();
	
	std::map<std::string, std::shared_ptr<IConfig>> GetConfigs();

	
private:
	struct ConfigData
	{
		std::shared_ptr<IConfig> defaultConfig;
		std::shared_ptr<IConfig> userConfig;
	};
	
	std::map<std::string, ConfigData> _configs;
	
	void LoadConfig(ConfigData& configs) const;
	void LoadDefaultConfig(std::shared_ptr<IConfig>& configs) const;
	
	void SaveConfig(ConfigData& configs) const;
	void SaveDefaultConfig(std::shared_ptr<IConfig>& configs) const;
};
}
