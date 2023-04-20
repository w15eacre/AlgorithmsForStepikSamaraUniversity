#pragma once

#include <vector>
#include <functional>

struct OrderInfo
{
	size_t deadline{0};
	size_t price{0};
};

class SchedulerAlgorithm
{
public:
	using OutputFunc = std::function<void(size_t)>;

	explicit SchedulerAlgorithm(const std::vector<OrderInfo>& orders, OutputFunc output);

	void Execute();

private:
	size_t Schedule(std::vector<bool>& scheduler);

private:
	std::vector<OrderInfo> m_orders{};
	size_t m_lastDeadline{};
	OutputFunc m_output;
};
