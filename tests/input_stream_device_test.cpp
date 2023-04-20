#include <gtest/gtest.h>

#include "input_stream_device.h"

#include <sstream>
#include <fstream>

TEST(InputStreamDevice, ContructorTest)
{
	auto ss = std::stringstream{};
	ASSERT_NO_THROW(InputStreamDevice{ss});

	auto fstream = std::fstream{};
	ASSERT_NO_THROW(InputStreamDevice{fstream});
}

TEST(InputStreamDevice, ReadEofStream)
{
	auto ss = std::stringstream{};
	auto inputStream = InputStreamDevice{ss};

	ASSERT_TRUE(inputStream.ReadLine(1024));
}

TEST(InputStreamDevice, ReadInvalidStream)
{
	auto ss = std::stringstream{};
	ss.setstate(std::ios_base::failbit);
	auto inputStream = InputStreamDevice{ss};

	ASSERT_THROW(inputStream.ReadLine(1024), std::runtime_error);
}

TEST(InputStreamDevice, ReadMaxSizeGreaterThenLine)
{
	constexpr std::string_view expected = "Abcdefghijklmnoprstu";
	auto ss = std::stringstream{};
	ss << expected;
	auto inputStream = InputStreamDevice{ss};

	auto line = inputStream.ReadLine(1024);
	ASSERT_TRUE(line);
	ASSERT_EQ(*line, expected);
}

TEST(InputStreamDevice, ReadMaxSizeLessThenLine)
{
	constexpr std::string_view expected = "Abcdefghijklmnoprstu";
	constexpr size_t length = 5;
	auto ss = std::stringstream{};
	ss << expected;
	auto inputStream = InputStreamDevice{ss};

	auto line = inputStream.ReadLine(length);
	ASSERT_TRUE(line);
	ASSERT_EQ(*line, std::string_view(expected.begin(), expected.begin() + length - 1));

	ASSERT_THROW(inputStream.ReadLine(length), std::runtime_error);
}

TEST(InputStreamDevice, ReadUntilNewLine)
{
	constexpr std::string_view expected = "Abcdefgh\nijklmno\nprstu";
	constexpr size_t length = 1024;
	auto ss = std::stringstream{};
	ss << expected;
	auto inputStream = InputStreamDevice{ss};

	auto line = inputStream.ReadLine(length);
	ASSERT_TRUE(line);
	ASSERT_EQ(*line, "Abcdefgh");

	line = inputStream.ReadLine(length);
	ASSERT_TRUE(line);
	ASSERT_EQ(*line, "ijklmno");

	line = inputStream.ReadLine(length);
	ASSERT_TRUE(line);
	ASSERT_EQ(*line, "prstu");
}
