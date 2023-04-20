#pragma once
#include <concepts>

template<typename T>
concept AlgorithmRequires = requires(T algorithm) {algorithm.Execute();};