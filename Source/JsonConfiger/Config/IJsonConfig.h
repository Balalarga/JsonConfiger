#pragma once

#include <string>

namespace JC
{
class JsonArchive;

class IJsonConfig
{
	friend class ConfigManager;
public:
	virtual ~IJsonConfig() = default;
	
	const std::string& GetFilepath() const { return _filepath; }
	const std::string& GetConfigName() const { return _name; }
	
	virtual void Serialize(JsonArchive* stream) = 0;
	
	
protected:
	IJsonConfig(const std::string& filepath);
	
	static std::string GetConfigNameFromPath(const std::string& filepath);
	
	
private:
	std::string _filepath;
	std::string _name;
};
}
