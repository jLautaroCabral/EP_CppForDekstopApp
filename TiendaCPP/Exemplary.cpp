#include "Exemplary.h"

Exemplary::Exemplary()
{
	editionNumber = 1;
	libraryUbication = "Exemplary ubication example";
}

Exemplary::Exemplary(const Exemplary& otherExemplary)
{
	modelID = otherExemplary.modelID;
	editionNumber = otherExemplary.editionNumber;
	book = otherExemplary.book;
	libraryUbication = otherExemplary.libraryUbication;
}

Exemplary::~Exemplary()
{
}
