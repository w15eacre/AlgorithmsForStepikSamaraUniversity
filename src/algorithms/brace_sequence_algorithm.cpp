#include "brace_sequence_algorithm.h"

#include <iostream>

BraceSequenceAlgorithm::BraceSequenceAlgorithm(size_t length, const std::vector<std::pair<char, char>>& whiteList,
											   BraceSequenceAlgorithm::OutputFunc output) :
		m_seqLength(length), m_whiteList(whiteList), m_output(std::move(output))
{
	if (!length)
	{
		throw std::invalid_argument("Length must be greater then 0");
	}

	if (length % 2 != 0)
	{
		throw std::invalid_argument("Length must be even");
	}

	if (!whiteList.size())
	{
		throw std::invalid_argument("WhiteList must be greater then 0");
	}
}

void BraceSequenceAlgorithm::Execute()
{
	std::stack<char> braceStack{};
	std::string result(m_seqLength, '\0');
	m_count = 0;
	Generate(0, braceStack, result);
}

void BraceSequenceAlgorithm::Generate(int idx, std::stack<char> &braceStack, std::string &result)
{

	if (idx == m_seqLength)
	{
		if (braceStack.empty())
		{
			m_output(result);
		}

		return;
	}

	for (auto [open, close]: m_whiteList)
	{
		braceStack.push(open);
		result[idx] = open;
		Generate(idx + 1, braceStack, result);
		braceStack.pop();

		if (!braceStack.empty() && braceStack.top() == open)
		{
			braceStack.pop();
			result[idx] = close;
			Generate(idx + 1, braceStack, result);
			braceStack.push(open);
		}
	}
}
