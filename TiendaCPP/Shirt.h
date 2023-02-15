#pragma once
#include "Garment.h"

#ifndef SHIRT_H
#define SHIRT_H

class Shirt : Garment
{
public:

	enum ShirtTypesFlag
	{
		MangaCorta = 1,
		CuelloMao = 2,
		//Short = 4,
		//Etc = 8
	};

	ShirtTypesFlag flag;
	~Shirt() override;

	friend inline ShirtTypesFlag operator|(ShirtTypesFlag a, ShirtTypesFlag b)
	{
		return static_cast<ShirtTypesFlag>(static_cast<int>(a) | static_cast<int>(b));
	}
};
#endif