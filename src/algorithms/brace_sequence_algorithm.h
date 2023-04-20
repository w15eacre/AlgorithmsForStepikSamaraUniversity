#pragma once

#include <string>
#include <stack>
#include <vector>
#include <functional>

class BraceSequenceAlgorithm
{
public:
	using OutputFunc = std::function<void(std::string_view)>;

	explicit BraceSequenceAlgorithm(size_t length, const std::vector<std::pair<char, char>>& whiteList, OutputFunc output);
	void Execute();

private:
	void Generate(int idx, std::stack<char>& braceStack, std::string& result);

private:
	size_t m_seqLength{0};
	size_t m_count{0};
	std::vector<std::pair<char, char>> m_whiteList{};
	OutputFunc m_output;
};
