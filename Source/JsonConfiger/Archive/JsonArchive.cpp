#include "JsonArchive.h"

namespace JC
{
JsonArchive::JsonArchive(const std::string& filepath, ArchiveMode mode):
	_filepath(filepath),
	_mode(mode)
{
}

JsonArchive::~JsonArchive()
{
	if (_mode == ArchiveMode::Write && !_json.is_null() && _stream.is_open())
	{
		_stream << _json.dump(_indent);
		_stream.close();
	}
}

bool JsonArchive::Open()
{
	if (_mode == ArchiveMode::Read)
	{
		_stream.open(_filepath, std::ios_base::in);
		_status = ArchiveStatus::Opened;
		try
		{
			_json = nlohmann::json::parse(_stream);
		}
		catch (...)
		{
			_status = ArchiveStatus::Opened;
			_stream.close();
			return false;
		}
		_status = ArchiveStatus::Read;
		_stream.close();
		return !_json.is_null();
	}
	
	if (_mode == ArchiveMode::Write)
	{
		_stream.open(_filepath, std::ios_base::out);
		_status = _stream.is_open() ? ArchiveStatus::Opened : ArchiveStatus::Closed;
		_json = nlohmann::json::object();
	}
	
	return true;
}

void JsonArchive::SetIndent(int indent)
{
	_indent = indent;
}
}
