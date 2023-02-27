#include "Book.h"
#include "DbModelItem.h"

#ifndef EXEMPLARY_H
#define EXEMPLARY_H
class Exemplary : public DbModelItem
{
public:
	Book book;
	int editionNumber = 0;
	std::string libraryUbication;
	Exemplary();
	Exemplary(const Exemplary& otherExemplary);
	~Exemplary();
};
#endif