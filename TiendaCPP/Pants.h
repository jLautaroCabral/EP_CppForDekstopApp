#pragma once
#include "Garment.h"

#ifndef PANTS_H
#define PANTS_H

class Pants : public Garment
{
public:
	enum PantsType
	{
		Comun = 0,
		Chupin = 1,
	};

	PantsType pantType;
	Pants();
	~Pants() override;
};
#endif