#include "input_stream_device.h"

std::optional<std::string> InputStreamDevice::ReadLine(size_t maxSize)
{
	if (m_stream.eof())
	{
		return std::nullopt;
	}

	if (m_stream.fail())
	{
		throw std::runtime_error("Input stream: error has occurred");
	}

	if (maxSize < 1)
	{
		throw std::runtime_error("Input stream: max size of string must be greater then 0");
	}

	std::string line(maxSize, '\0');
	m_stream.getline(line.data(), line.size());
	return line.c_str();
}