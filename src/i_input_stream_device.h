#pragma once

#include <string>
#include <optional>
#include <memory>

class IInputStreamDevice
{
public:
	virtual ~IInputStreamDevice() = default;

	virtual std::optional<std::string> ReadLine(size_t maxSize) = 0;
};

using IStreamDevicePtr = std::unique_ptr<IInputStreamDevice>;
