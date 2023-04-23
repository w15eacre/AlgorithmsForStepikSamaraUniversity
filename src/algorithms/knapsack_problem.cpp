#include "knapsack_problem.h"

#include <stdexcept>

KnapsackProblem::KnapsackProblem(const std::vector<Staff> &staff, size_t capacity, const OutputFunc& output):
m_capacity(capacity), m_staff(staff), m_output(output)
{
	std::sort(std::begin(m_staff), std::end(m_staff), [](const auto& lhs, const auto& rhs) {
		auto lval = lhs.price / lhs.width; // must be lhs.width % lhs.price
		auto rval = rhs.price / rhs.width; // must be hs.width % rhs.price

		return lval > rval;
	});
}

void KnapsackProblem::Execute()
{
	size_t rest = m_capacity;
	size_t price = 0;

	int lastItemIndex = -1;
	for(size_t i = 0; i < m_staff.size(); ++i)
	{
		if (m_staff[i].width > rest)
		{
			break;
		}

		rest -= m_staff[i].width;
		price += m_staff[i].price;
		lastItemIndex = i;

		if (rest == 0)
		{
			m_output(price);
			return;
		}
	}

	if (lastItemIndex == -1)
	{
		m_output(0);
		return;
	}

	if (lastItemIndex + 1 >= m_staff.size())
	{
		m_output(price);
		return;
	}

	auto val = m_staff[lastItemIndex + 1].price / m_staff[lastItemIndex + 1].width;
	price += val * rest;

	m_output(price);
}
