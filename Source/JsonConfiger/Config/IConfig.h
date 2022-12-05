#pragma once

#include <string>
#include "ThirdParty/json.hpp"

namespace JC
{
class IConfig
{
public:
	IConfig(const std::string& filepath);
	virtual ~IConfig() = default;
	
	const std::string& GetFilepath() const { return _filepath; }
	bool IsDefaultOnly() const { return _bDefaultOnly; }
	
	virtual void Serialize(std::ostream& stream) = 0;
	
	virtual bool operator!=(const IConfig& oth) { return false; }


protected:
	IConfig() = default;

	
private:
	std::string _filepath;
	const bool _bDefaultOnly;
	bool _bHaveGui;
};
}