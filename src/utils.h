#pragma once
#include <sstream>

template<typename T>
void GetValue(const std::string& data, T& value)
{
	std::stringstream ss(data);
	ss >> value;
}
