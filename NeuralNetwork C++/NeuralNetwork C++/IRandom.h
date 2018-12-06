#pragma once
#include "stdafx.h"
#include <cstdint>

class IRandom
{
public:

	/// <summary>
	/// Finalizes an instance of the class.
	/// </summary>
	virtual ~IRandom() = default;

	/// <summary>
	/// return a positive int
	/// </summary>
	virtual std::int32_t Next() = 0;

	virtual std::int32_t Next(std::int32_t maxValue) = 0;

	virtual std::int32_t Next(std::int32_t minValue, std::int32_t maxValue) = 0;


	virtual std::double_t NextDouble() = 0;

	virtual std::double_t NextDouble(std::double_t minValue, std::double_t maxValue) = 0;

};