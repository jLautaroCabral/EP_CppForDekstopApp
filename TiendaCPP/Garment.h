#pragma once

#ifndef GARMENT_H
#define GARMENT_H

class Garment
{
	enum GarmentType { Shirt, Pants };
	enum QualityType { Standar, Premium };

public:
	virtual ~Garment() = 0;
	GarmentType garmentType;
	QualityType qualityType;
};
#endif