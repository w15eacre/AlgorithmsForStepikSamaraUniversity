#include "gas_station.h"

#include <stdexcept>

namespace {
int64_t BinSearchGasStation(const std::vector<size_t>& gasStations, size_t leftIdx, size_t rightIdx, size_t currentDistance)
{
	if (currentDistance >= gasStations.back())
	{
		return gasStations.size() - 1;
	}

	if (rightIdx - leftIdx == 1)
	{
		return leftIdx;
	}

	size_t middle = (leftIdx + rightIdx) / 2;
	if (gasStations[middle] <= currentDistance)
	{
		leftIdx = middle;
	}
	else if (gasStations[middle] > currentDistance)
	{
		rightIdx = middle;
	}

	return BinSearchGasStation(gasStations, leftIdx, rightIdx, currentDistance);
}
}

GasStation::GasStation(size_t distance, size_t fullGasDistance, const std::vector<size_t>& gasStations, const OutputFunc& output):
	m_distance(distance), m_fullGasDistance(fullGasDistance), m_gasStations(gasStations), m_out(output)
{
}

void GasStation::Execute()
{
	size_t currentDistance = 0;
	size_t count = 0;

	size_t idx = 0;
	while(currentDistance + m_fullGasDistance < m_distance)
	{
		idx = BinSearchGasStation(m_gasStations, idx, m_gasStations.size() - 1, currentDistance + m_fullGasDistance);
		if (idx < 0)
		{
			throw std::runtime_error("Gas station not found");
		}

		currentDistance = m_gasStations[idx];
		++count;
	}

	m_out(count);
}
