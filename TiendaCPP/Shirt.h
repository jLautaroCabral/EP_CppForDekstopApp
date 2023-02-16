#pragma once
#include "Garment.h"

#ifndef SHIRT_H
#define SHIRT_H

class Shirt : public Garment
{
public:

	enum ShirtMangaTypes
	{
		MangaLarga = 0,
		MangaCorta = 1,
	};

	enum ShirtCuelloTypes
	{
		CuelloComun = 0,
		CuelloMao = 1,
	};

	ShirtMangaTypes mangaType;
	ShirtCuelloTypes cuelloType;

	Shirt();
	~Shirt() override;
};
#endif