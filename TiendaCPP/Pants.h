#pragma once
#include "Garment.h"

#ifndef PANTS_H
#define PANTS_H

class Pants : Garment
{
public:
	enum PantsTypesFlag
	{
		Chupin = 1,
		//Jean = 2,
		//Short = 4,
		//Etc = 8
	};

	PantsTypesFlag flag;
	~Pants() override;

	friend inline PantsTypesFlag operator|(PantsTypesFlag a, PantsTypesFlag b)
	{
		return static_cast<PantsTypesFlag>(static_cast<int>(a) | static_cast<int>(b));
	}
};
#endif