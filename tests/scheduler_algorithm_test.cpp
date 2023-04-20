#include <gtest/gtest.h>

#include "algorithms/scheduler_algorithm.h"
#include "file_reader.h"
#include "test_config.h"

namespace {
std::vector<OrderInfo> GetOrders(std::string_view filename)
{
	FileReader file{GetResourcePath() / filename};

	std::vector<OrderInfo> orders(file.ReadValue<size_t>());

	for (auto& order: orders)
	{
		order.deadline = file.ReadValue<size_t>();
		order.price = file.ReadValue<size_t>();
	}

	return orders;
}

size_t CalculateSalary(const std::vector<OrderInfo>& orders)
{
	size_t result{};
	auto output = [&result](size_t res) {result = res;};
	SchedulerAlgorithm algorithm{orders, output};
	algorithm.Execute();

	return result;
}

}

TEST(SchedulerTest, ConstructFailed)
{
	ASSERT_THROW(SchedulerAlgorithm({}, SchedulerAlgorithm::OutputFunc{}), std::invalid_argument);
}

TEST(SchedulerAlgorithm, MinimalExample)
{
	std::vector<OrderInfo> orders;
	ASSERT_NO_THROW(orders = GetOrders("scheduler_1.in"));

	ASSERT_EQ(CalculateSalary(orders), 13);
}


TEST(SchedulerAlgorithm, SchedulerSortedTest)
{
	std::vector<OrderInfo> orders;
	ASSERT_NO_THROW(orders = GetOrders("schedule_sorted.in"));

	ASSERT_EQ(CalculateSalary(orders), 374);
}

TEST(SchedulerAlgorithm, SchedulerUnsortedTest)
{
	std::vector<OrderInfo> orders;
	ASSERT_NO_THROW(orders = GetOrders("schedule_unsorted.in"));
	ASSERT_EQ(CalculateSalary(orders), 2305658251934);
}