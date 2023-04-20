#pragma once

#include "i_input_stream_device.h"

#include <istream>

class InputStreamDevice: public  IInputStreamDevice
{
public:
	template<typename T>
	explicit InputStreamDevice(T& stream): m_stream(stream) {}

	InputStreamDevice(const InputStreamDevice& device) = delete;
	InputStreamDevice& operator=(const InputStreamDevice& device) = delete;

	InputStreamDevice(InputStreamDevice&& device) = delete;
	InputStreamDevice& operator=(InputStreamDevice&& device) = delete;

	std::optional<std::string> ReadLine(size_t maxSize) override;

private:
	std::istream& m_stream;
};
