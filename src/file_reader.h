#pragma once

#include <fstream>
#include <filesystem>

class FileReader
{
public:
	explicit FileReader(const std::filesystem::path& path);
	~FileReader();

	FileReader(const FileReader& reader) = delete;
	FileReader& operator=(const FileReader& reader) = delete;

	FileReader(FileReader&& reader) noexcept = default;
	FileReader& operator=(FileReader&& reader) = default;

	template<typename T>
	T ReadValue()
	{
		T result{};
		m_fstream >> result;
		return result;
	}

	std::fstream &GetFileStream();

private:
	std::fstream m_fstream{};
};
