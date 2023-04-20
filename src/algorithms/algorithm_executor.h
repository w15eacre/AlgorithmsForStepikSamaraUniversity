#pragma once

#include "algorithm_concept.h"

#include <utility>
#include <algorithm>

class AlgorithmExecutor
{
public:
	template<AlgorithmRequires T, AlgorithmRequires ...Args>
	void Execute(T&& algorithm, Args&&... args)
	{
		algorithm.Execute();

		if constexpr(sizeof...(args) > 0)
		{
			Execute(std::forward<Args>(args)...);
		}
	}
};
