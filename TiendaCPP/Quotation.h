#pragma once
#include "Garment.h"
#include "Seller.h"

#ifndef QUOTATION_H
#define QUOTATION_H
class Quotation
{
public:
	Garment* garmentPtr;
	std::string sellerID;
	int unitaryPrice;
	int garmentQuantity;
	float quotationResult;
	time_t quotationDate;
	int quotationID;
	Quotation();
	Quotation(Garment* garmentPtr, std::string sellerID, int unitaryPrice, int garmentQuantity, int quotationResult);
};
#endif