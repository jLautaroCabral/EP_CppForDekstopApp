#pragma once
#include "Garment.h"

#ifndef PANTS_H
#define PANTS_H

class Pants : public Garment
{
public:
	enum PantsTypesFlag
	{
		Normal = 0,
		Chupin = 1,
		//Jean = 2,
		//Short = 4,
		//Etc = 8
	};

	PantsTypesFlag flag;
	Pants();
	~Pants() override;

	friend inline PantsTypesFlag operator|(PantsTypesFlag a, PantsTypesFlag b)
	{
		return static_cast<PantsTypesFlag>(static_cast<int>(a) | static_cast<int>(b));
	}
};
#endif