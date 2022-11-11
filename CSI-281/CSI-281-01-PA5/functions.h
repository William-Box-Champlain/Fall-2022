#pragma once
#include <random>

namespace wb
{
	int getRandomNumber()
	{
		return (std::rand() * std::rand()) % 1000001;
	}
}