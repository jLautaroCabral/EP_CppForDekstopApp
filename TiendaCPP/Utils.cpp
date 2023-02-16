#include "Utils.h"
#include <iostream>
#include <algorithm>

bool Utils::isNumber(const std::string& str)
{
	for (char const& c : str) {
		if (std::isdigit(c) == 0) return false;
	}
	return true;
}