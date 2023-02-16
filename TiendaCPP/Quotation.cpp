#include "Quotation.h"

Quotation::Quotation(Garment* garmentPtr, std::string sellerID, int unitaryPrice, int garmentQuantity, int quotationResult)
{
	this->garmentPtr = garmentPtr;
	this->sellerID = sellerID;
	this->unitaryPrice = unitaryPrice;
	this->garmentQuantity = garmentQuantity;
	this->quotationResult = quotationResult;
}

Quotation::Quotation()
{
}
