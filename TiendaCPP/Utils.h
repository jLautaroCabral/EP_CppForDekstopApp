#pragma once
#include <string>

#ifndef UTILS_H
#define UTILS_H
class Utils
{
public:
	static bool IsNumber(const std::string& s);
	static void StringToConstWchar_TPointer(const std::string& string, const wchar_t*&);
	static const wchar_t* StringToConstWchar_TPointer(const std::string& string);
	static std::string* WCharToString_TPointer(wchar_t* wcharString);
};
#endif