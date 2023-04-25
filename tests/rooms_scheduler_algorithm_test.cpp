#include <gtest/gtest.h>

#include "algorithms/rooms_scheduler.h"
#include "file_reader.h"
#include "test_config.h"

namespace {
std::vector<Period> GetPeriods(std::string_view filename)
{
	FileReader file{GetResourcePath() / filename};

	std::vector<Period> periods(file.ReadValue<size_t>());

	for (auto& period: periods)
	{
		period.start = file.ReadValue<size_t>();
		period.finish = file.ReadValue<size_t>();
	}

	return periods;
}

size_t CalculateLectureCount(const std::vector<Period>& periods)
{
	size_t result{};
	auto output = [&result](size_t res) {result = res;};
	RoomsScheduler algorithm{periods, output};
	algorithm.Execute();

	return result;
}
}

TEST(RoomsSchedulerTest, ConstructFailed)
{
	ASSERT_THROW(RoomsScheduler({}, RoomsScheduler::OutputFunc{}), std::invalid_argument);
}

TEST(RoomsSchedulerTest, MinimalExample)
{
	std::vector<Period> periods;
	ASSERT_NO_THROW(periods = GetPeriods("room_scheduler_minimal.in"));
	ASSERT_EQ(CalculateLectureCount(periods), 2);
}

TEST(RoomsSchedulerTest, RoomsScheduler1)
{
	std::vector<Period> periods;
	ASSERT_NO_THROW(periods = GetPeriods("rooms_scheduler_1.in"));
	ASSERT_EQ(CalculateLectureCount(periods), 50038);
}

TEST(RoomsSchedulerTest, RoomsScheduler2)
{
	std::vector<Period> periods;
	ASSERT_NO_THROW(periods = GetPeriods("rooms_scheduler_2.in"));
	ASSERT_EQ(CalculateLectureCount(periods), 5);
}

TEST(RoomsSchedulerTest, RoomsScheduler3)
{
	std::vector<Period> periods;
	ASSERT_NO_THROW(periods = GetPeriods("rooms_scheduler_3.in"));
	ASSERT_EQ(CalculateLectureCount(periods), 6);
}