#include "room_scheduler.h"

#include <algorithm>

RoomScheduler::RoomScheduler(const std::vector<Period> &periods, const RoomScheduler::OutputFunc &output):
	m_output(output)
{
	if (periods.empty())
	{
		throw std::invalid_argument("Period is empty");
	}

	m_period = periods;
	std::sort(std::begin(m_period), std::end(m_period), [](const auto& lhs, const auto& rhs) {
		return lhs.finish < rhs.finish;
	});
}

void RoomScheduler::Execute()
{
	size_t count = 0;
	size_t lastFinish = 0;
	for (auto [start, finish]: m_period)
	{
		if (lastFinish <= start)
		{
			lastFinish = finish;
			++count;
		}
	}

	m_output(count);
}
