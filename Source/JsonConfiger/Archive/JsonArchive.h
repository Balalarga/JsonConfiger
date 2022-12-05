#pragma once
#include <string>
#include <fstream>
#include "JsonConfiger/ThirdParty/json.hpp"

namespace JC
{
enum class ArchiveMode: uint8_t
{
	Read, Write
};

enum class ArchiveStatus: uint8_t
{
	Closed = 0, Opened, Read
};

class JsonArchive
{
public:
	JsonArchive(const std::string& filepath, ArchiveMode mode);
	virtual ~JsonArchive();

	void SetIndent(int indent);
	int GetIndent() const { return _indent; }

	bool Open();
	ArchiveStatus GetStatus() { return _status; }
	
	template<class T>
	bool Serialize(const std::string& tag, T& val)
	{
		if (_mode == ArchiveMode::Read)
		{
			if (!_json.contains(tag))
				return false;
			
			val = _json[tag].get<T>();
		}
		else if (_mode == ArchiveMode::Write)
		{
			_json[tag] = val;
		}
		return true;
	}

	const nlohmann::json& GetJson() const { return _json; }
	
private:
	const std::string _filepath;
	const ArchiveMode _mode;
	std::fstream _stream;

	ArchiveStatus _status = ArchiveStatus::Closed;
	
	nlohmann::json _json;
	int _indent = 4;
};
}
