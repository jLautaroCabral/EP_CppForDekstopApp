#include "UtilsUI.h"

bool UtilsUI::TryGetStringFromInputField(HWND hDlg, int resourceID, std::string fieldLabelName, std::string& outString)
{
	const int maxAmountOfCharacters = 100;
	int inputStrLength;

	HWND hInpfBookName = GetDlgItem(hDlg, resourceID);
	inputStrLength = GetWindowTextLength(hInpfBookName);
	

	if (inputStrLength > maxAmountOfCharacters)
	{
		std::string errorMessageToShow = "Has excedido la cantidad de caracteres permitidos(" + std::to_string(maxAmountOfCharacters) + ") en el campo '" + fieldLabelName + "'";

		MessageBox(NULL, Utils::StringToConstWchar_TPointer(errorMessageToShow), L"Error", MB_ICONERROR);
		return false;
	}
	
	wchar_t inputStr[maxAmountOfCharacters];
	GetWindowText(hInpfBookName, inputStr, inputStrLength + 1);

	// EJEMPLO DE LIMPIEZA A EVALUAR
	std::string* strPointer = Utils::WCharToString_TPointer(inputStr);
	//outString = *Utils::WCharToString_TPointer(inputStr);
	outString = *strPointer;
	delete strPointer;
	return true;
}
