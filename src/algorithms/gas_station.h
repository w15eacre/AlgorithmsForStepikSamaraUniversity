#pragma once

#include <functional>

class GasStation
{
public:
	using OutputFunc = std::function<void(size_t)>;
	explicit GasStation(size_t distance, size_t fullGasDistance, const std::vector<size_t>& gasStations, const OutputFunc& output);

	void Execute();

private:
	size_t m_distance{};
	size_t m_fullGasDistance{};
	std::vector<size_t> m_gasStations{};

	OutputFunc m_out{};
};
