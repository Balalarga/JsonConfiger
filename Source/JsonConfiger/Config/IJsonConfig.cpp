#include "IJsonConfig.h"

namespace JC
{
IJsonConfig::IJsonConfig(const std::string& filepath):
	_filepath(filepath),
	_name(GetConfigNameFromPath(filepath))
{
}

std::string IJsonConfig::GetConfigNameFromPath(const std::string& filepath)
{
	size_t nameStart = filepath.find_last_of('\\');
	if (nameStart == std::string::npos)
		nameStart = filepath.find_last_of('/');

	if (nameStart == std::string::npos)
		nameStart = 0;
	else
		++nameStart;

	size_t nameEnd = filepath.find_last_of('.');
	if (nameEnd == std::string::npos)
		nameEnd = filepath.length();
	
	return filepath.substr(nameStart, nameEnd);
}
}
