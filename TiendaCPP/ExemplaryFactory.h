#pragma once
#include "Exemplary.h"
#ifndef EXEMPLARY_FACTORY
#define EXEMPLARY_FACTORY
class ExemplaryFactory
{
private:
	static const std::string libraryUbications[4];
public:
	static Exemplary* CreateRandomExemplary();
	static Exemplary* CreateExemplary();
};
#endif