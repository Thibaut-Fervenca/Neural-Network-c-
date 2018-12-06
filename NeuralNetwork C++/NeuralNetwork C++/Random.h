#pragma once
#include "stdafx.h"
#include <cstdint>
#include <random>
#include "IRandom.h"
class Random :
	public IRandom
{
	///A Mersenne Twister pseudo-random generator of 32-bit numbers with a state size of 19937 bits.
	///http://www.cplusplus.com/reference/random/mt19937/
	std::mt19937 randomNumberGenerator;
	

public:
	Random(std::uint_least32_t seed);
	Random() : Random(std::_Random_device()) {};
	std::int32_t Next() override;
	std::int32_t Next(std::int32_t maxValue) override;
	std::int32_t Next(std::int32_t minValue, std::int32_t maxValue) override;
	std::double_t NextDouble() override;
	std::double_t NextDouble(std::double_t minValue, std::double_t maxValue) override;
	
};

