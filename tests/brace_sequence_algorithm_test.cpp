#include <gtest/gtest.h>

#include "algorithms/brace_sequence_algorithm.h"
#include "algorithms/algorithm_executor.h"
#include "input_stream_device.h"
#include "test_config.h"
#include "utils.h"
#include "file_reader.h"

#include <fstream>
#include <charconv>

namespace {
void GetBraces(std::string_view seq, std::vector<std::pair<char, char>> &values)
{
	if (seq.empty() || seq.size() % 2 != 0)
	{
		return;
	}

	values.reserve(seq.size() / 2);
	for (int i = 0; i < seq.size() - 1; i += 2)
	{
		values.emplace_back(seq[i], seq[i + 1]);
	}
}

std::vector<std::string> GetExpectedValues()
{
	std::fstream file{GetResourcePath() / "brace_seq_2.out"};
	[&file](){ ASSERT_TRUE(file.is_open());}();

	std::vector<std::string> expected{};
	InputStreamDevice device(file);
	while (auto result = device.ReadLine(1024))
	{
		expected.emplace_back(std::move(*result));
	}

	return expected;
}

}

TEST(BraceSequenceAlgorithmTest, ContructFailed)
{
	ASSERT_THROW(
			(BraceSequenceAlgorithm{0, {{'(', ')'}},
									BraceSequenceAlgorithm::OutputFunc{}}),
			std::invalid_argument);

	ASSERT_THROW(
			(BraceSequenceAlgorithm{1, {},
									BraceSequenceAlgorithm::OutputFunc{}}),
			std::invalid_argument);
}

TEST(BraceSequenceAlgorithmTest, SeqLenghtIs4)
{
	FileReader file{GetResourcePath() / "brace_seq_2.in"};
	size_t length = file.ReadValue<size_t>();

	std::vector<std::pair<char, char>> braces;
	ASSERT_NO_THROW(GetBraces(file.ReadValue<std::string>(), braces));
	ASSERT_NO_THROW(braces.size() % 2);

	std::vector<std::string> result{};
	auto output = [&result](std::string_view data) { result.emplace_back(std::string{data}); };

	auto algorithm = BraceSequenceAlgorithm{length, braces, output};
	AlgorithmExecutor exec{};
	exec.Execute(algorithm);

	ASSERT_EQ(result, GetExpectedValues());
}

TEST(BraceSequenceAlgorithmTest, SeqLenghtIs6WithNumber20)
{
	constexpr size_t Length = 6;
	constexpr size_t Index = 19;
	std::vector<std::string> result{};
	auto output = [&result](std::string_view data) { result.emplace_back(std::string{data}); };

	auto algorithm = BraceSequenceAlgorithm{Length, {{'(', ')'}, {'[', ']'}}, output};
	AlgorithmExecutor exec{};
	exec.Execute(algorithm);
	ASSERT_TRUE(result.size() > Index);

	ASSERT_EQ(result[Index], "([][])");
}

TEST(BraceSequenceAlgorithmTest, SeqLenghtIs14WithNumber8233)
{
	constexpr size_t Length = 14;
	constexpr size_t Index = 8232;

	std::vector<std::string> result{};
	auto output = [&result](std::string_view data) { result.emplace_back(std::string{data}); };

	auto algorithm = BraceSequenceAlgorithm{Length, {{'(', ')'}, {'[', ']'}}, output};
	AlgorithmExecutor exec{};
	exec.Execute(algorithm);
	ASSERT_TRUE(result.size() > Index);

	ASSERT_EQ(result[Index], "(([]())([]))()");
}

