#include <gtest/gtest.h>

#include "file_reader.h"
#include "test_config.h"
#include "algorithms/knapsack_problem.h"

namespace {
void GetInputParams(std::string_view filename, size_t &capacity, std::vector<Staff> &staff)
{
	FileReader file(GetResourcePath() / filename);

	auto staffCount = file.ReadValue<size_t>();
	staff.resize(staffCount);

	capacity = file.ReadValue<size_t>();

	for (auto& v: staff)
	{
		v.width = file.ReadValue<size_t>();
		v.price = file.ReadValue<size_t>();
	}
}
}

TEST(KnapsackProblemTest, MinimalExample)
{
	std::vector<Staff> staff{};
	size_t capacity{};
	GetInputParams("knapsack_problem_minimal.in", capacity, staff);

	size_t result{};
	auto out = [&result](auto value) {result = value;};

	KnapsackProblem problem(staff, capacity, out);
	problem.Execute();
	ASSERT_EQ(result, 18);
}

TEST(KnapsackProblemTest, Example1)
{
	std::vector<Staff> staff{};
	size_t capacity{};
	GetInputParams("knapsack_problem_1.in", capacity, staff);

	size_t result{};
	auto out = [&result](auto value) {result = value;};

	KnapsackProblem problem(staff, capacity, out);
	problem.Execute();
	ASSERT_EQ(result, 550);
}

TEST(KnapsackProblemTest, Example2)
{
	std::vector<Staff> staff{};
	size_t capacity{};
	GetInputParams("knapsack_problem_2.in", capacity, staff);

	size_t result{};
	auto out = [&result](auto value) {result = value;};

	KnapsackProblem problem(staff, capacity, out);
	problem.Execute();
	ASSERT_EQ(result, 7909205);
}
