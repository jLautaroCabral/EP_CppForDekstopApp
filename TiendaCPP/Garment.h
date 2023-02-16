#pragma once
#include <string>

#ifndef GARMENT_H
#define GARMENT_H



class Garment
{
	enum GarmentType { Shirt, Pants };
	enum QualityType { Standar, Premium };
	
public:
	Garment();
	virtual ~Garment() = 0;
	std::string garmentName = "";
	GarmentType garmentType = Shirt;
	QualityType qualityType = Standar;
};
#endif