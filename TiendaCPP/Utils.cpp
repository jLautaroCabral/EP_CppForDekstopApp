#include "Utils.h"
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool Utils::IsNumber(const std::string& str)
{
	for (char const& c : str) {
		if (std::isdigit(c) == 0) return false;
	}
	return true;
}


void Utils::StringToConstWchar_TPointer(const std::string& stringToConvert, const wchar_t*& result)
{
	std::string string = stringToConvert;

	// TODO: RECORDAR LIBERAR ESTOOOO
	// Probablemente tenga que agregar un método para liberar toda la memoria de la calse Utils
	std::wstring* wide_string = new std::wstring();
	*wide_string = std::wstring(string.begin(), string.end());

	result = (*wide_string).c_str();
}

const wchar_t* Utils::StringToConstWchar_TPointer(const std::string& stringToConvert)
{
	std::string string = stringToConvert;

	// TODO: RECORDAR LIBERAR ESTOOOO
	// Probablemente tenga que agregar un método para liberar toda la memoria de la calse Utils
	std::wstring* wide_string = new std::wstring();
	*wide_string = std::wstring(string.begin(), string.end());

	const wchar_t* result = (*wide_string).c_str();

	return result;
}

std::string* Utils::WCharToString_TPointer(wchar_t* wcharString)
{
	std::wstring wide_string(wcharString);
	std::string* stdStr = new std::string(wide_string.begin(), wide_string.end());

	return stdStr;
}


