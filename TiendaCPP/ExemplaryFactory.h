#include "Exemplary.h"
#include "Book.h"

#ifndef EXEMPLARY_FACTORY
#define EXEMPLARY_FACTORY
class ExemplaryFactory
{
private:
	static const std::string libraryUbications[4];
public:
	static Exemplary* CreateRandomExemplary();
	static Exemplary* CreateRandomExemplary(Book* book);
	static Exemplary* CreateExemplary(int editionNumber, std::string libraryUbication, int bookModelId);
};
#endif