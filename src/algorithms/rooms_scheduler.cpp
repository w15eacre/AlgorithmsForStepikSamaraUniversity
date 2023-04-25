#include "rooms_scheduler.h"

#include <algorithm>
#include <set>

RoomsScheduler::RoomsScheduler(const std::vector<Period> &periods, const RoomsScheduler::OutputFunc &output):
		m_output(output)
{
	if (periods.empty())
	{
		throw std::invalid_argument("Period is empty");
	}

	m_period = periods;
	std::sort(std::begin(m_period), std::end(m_period), [](const auto& lhs, const auto& rhs) {
		return lhs.start < rhs.start;
	});
}

void RoomsScheduler::Execute()
{
	std::multiset<size_t> rooms{};
	for (const auto& period: m_period)
	{
		auto it = rooms.upper_bound(period.start);
		if (it == std::cbegin(rooms))
		{
			rooms.insert(period.finish);
			continue;
		}

		auto node = it == std::cend(rooms) ? 	rooms.extract(std::begin(rooms)):
																	rooms.extract(--it);
		node.value() = period.finish;
		rooms.insert(std::move(node));
	}

	m_output(rooms.size());
}
