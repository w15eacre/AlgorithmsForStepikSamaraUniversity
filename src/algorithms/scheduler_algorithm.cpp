#include "scheduler_algorithm.h"

#include <algorithm>
#include <iostream>

SchedulerAlgorithm::SchedulerAlgorithm(const std::vector<OrderInfo>& orders, OutputFunc output):
	m_output(std::move(output))
{
	if (orders.empty())
	{
		throw std::invalid_argument("Order list is empty");
	}

	m_orders = orders;
	std::sort(std::begin(m_orders), std::end(m_orders),
			  [this](const auto& lhs, const auto& rhs) {
		m_lastDeadline = std::max(std::max(m_lastDeadline, rhs.deadline), lhs.deadline);
		return lhs.price > rhs.price;
	});
}

void SchedulerAlgorithm::Execute()
{
	std::vector<bool> scheduler(m_lastDeadline, false);
	m_output(Schedule(scheduler));

}

size_t SchedulerAlgorithm::Schedule(std::vector<bool> &scheduler)
{
	size_t totalSalary = 0;
	for (auto&& [deadline, price]: m_orders)
	{
		while (scheduler[deadline])
		{
			deadline--;
		}

		if (deadline == 0)
		{
			continue;
		}

		scheduler[deadline] = true;
		totalSalary += price;
	}

	return totalSalary;
}