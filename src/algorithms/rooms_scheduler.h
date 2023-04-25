#pragma once

#include <functional>

struct Period
{
	size_t start;
	size_t finish;
};

class RoomsScheduler
{
public:
	using OutputFunc = std::function<void(size_t)>;

	explicit RoomsScheduler(const std::vector<Period>& periods, const OutputFunc& output);

	void Execute();

private:
	std::vector<Period> m_period;
	OutputFunc m_output;
};
