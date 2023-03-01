#include <string>
#include "framework.h"
#include "Utils.h"

#ifndef UTILS_UI_H
#define UTILS_UI_H
class UtilsUI
{
public:
	static bool IsNumber(const std::string& s);
	static bool TryGetStringFromInputField(HWND hDlg, int resourceID, std::string fieldLabelName, std::string& outString);
};
#endif