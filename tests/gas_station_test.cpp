#include <gtest/gtest.h>

#include "algorithms/gas_station.h"
#include "test_config.h"
#include "file_reader.h"

namespace {
void GetInputParams(std::string_view filename, size_t& distance, size_t& fullGasDistance, std::vector<size_t>& gasStations)
{
	FileReader file(GetResourcePath() / filename);

	auto gasCount = file.ReadValue<size_t>();
	distance = file.ReadValue<size_t>();
	fullGasDistance = file.ReadValue<size_t>();

	gasStations.resize(gasCount);
	for (auto& gas: gasStations)
	{
		gas = file.ReadValue<size_t>();
	}
}

size_t CalculateMinimalGasCount(size_t distance, size_t fullGasDistance, const std::vector<size_t>& gasStations)
{
	size_t count = 0;
	auto output = [&count](size_t result) {count = result;};
	GasStation alg{distance, fullGasDistance, gasStations, output};
	alg.Execute();

	return count;
}

}

TEST(GasStationTest, MinimalExample)
{
	size_t distance;
	size_t fullGasDistance;
	std::vector<size_t> gasStations;
	ASSERT_NO_THROW(GetInputParams("gas_station_minimal.in", distance, fullGasDistance, gasStations));

	ASSERT_EQ(CalculateMinimalGasCount(distance, fullGasDistance, gasStations), 2);
}

TEST(GasStationTest, GasStation1)
{
	size_t distance;
	size_t fullGasDistance;
	std::vector<size_t> gasStations;
	ASSERT_NO_THROW(GetInputParams("gas_station_1.in", distance, fullGasDistance, gasStations));

	ASSERT_EQ(CalculateMinimalGasCount(distance, fullGasDistance, gasStations), 4);
}

TEST(GasStationTest, GasStation2)
{
	size_t distance;
	size_t fullGasDistance;
	std::vector<size_t> gasStations;
	ASSERT_NO_THROW(GetInputParams("gas_station_2.in", distance, fullGasDistance, gasStations));

	ASSERT_EQ(CalculateMinimalGasCount(distance, fullGasDistance, gasStations), 1021);
}