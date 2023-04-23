#include <functional>
#pragma once

struct Staff
{
	size_t width{};
	size_t price{};
};

class KnapsackProblem
{
public:
	using OutputFunc = std::function<void(size_t)>;

	explicit KnapsackProblem(const std::vector<Staff>& staff, size_t capacity, const OutputFunc& output);

	void Execute();

private:
	size_t m_capacity{};
	std::vector<Staff> m_staff;

	OutputFunc m_output{};
};
