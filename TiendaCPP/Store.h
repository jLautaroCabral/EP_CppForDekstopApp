#pragma once
#include <string>
#include <list>
#include "Seller.h"
#include "Quotation.h"
#include "Garment.h"

#ifndef STORE_H
#define STORE_H
class Store
{
public:
	std::string storeName;
	std::string storeAddress;
	Store();
	Seller currentSeller;
	std::list<Garment> garments;
	std::list<Quotation> quotationHistory;
};
#endif