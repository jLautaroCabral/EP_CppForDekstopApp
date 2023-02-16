#pragma once
#include "Garment.h"

#ifndef SHIRT_H
#define SHIRT_H

class Shirt : public Garment
{
public:

	enum ShirtTypesFlag
	{
		Normal = 0,
		MangaCorta = 1,
		CuelloMao = 2,
		//Etc = 4,
	};

	ShirtTypesFlag flag;
	Shirt();
	~Shirt() override;

	friend inline ShirtTypesFlag operator|(ShirtTypesFlag a, ShirtTypesFlag b)
	{
		return static_cast<ShirtTypesFlag>(static_cast<int>(a) | static_cast<int>(b));
	}
};
#endif