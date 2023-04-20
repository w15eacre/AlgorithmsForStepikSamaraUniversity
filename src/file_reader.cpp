#include "file_reader.h"

FileReader::FileReader(const std::filesystem::path &path)
{
	m_fstream = std::fstream(path);
	if (!m_fstream.is_open())
	{
		throw std::invalid_argument("FileReader: file not found");
	}
}

FileReader::~FileReader()
{
	m_fstream.close();
}
