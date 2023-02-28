#include "ExemplaryFactory.h"

const std::string ExemplaryFactory::libraryUbications[4] = { "Estanteria A", "Estanteria B", "Estanteria C", "Estanteria D" };

Exemplary* ExemplaryFactory::CreateRandomExemplary()
{
	Exemplary* exemplary = new Exemplary();
	exemplary->bookID = -1;
	exemplary->editionNumber = rand() % 5;
	exemplary->libraryUbication = libraryUbications[rand() % (std::size(libraryUbications) - 1)];
    return exemplary;
}

Exemplary* ExemplaryFactory::CreateExemplary()
{
    return nullptr;
}
