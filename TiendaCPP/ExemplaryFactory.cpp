#include "ExemplaryFactory.h"


const std::string ExemplaryFactory::libraryUbications[4] = { "Estanteria A", "Estanteria B", "Estanteria C", "Estanteria D" };

Exemplary* ExemplaryFactory::CreateRandomExemplary()
{
	Exemplary* exemplary = new Exemplary();
	exemplary->bookID = -1;
	exemplary->editionNumber = (rand() % 5) + 1;
	exemplary->libraryUbication = libraryUbications[rand() % (std::size(libraryUbications))];
    return exemplary;
}

Exemplary* ExemplaryFactory::CreateRandomExemplary(Book* book)
{
	Exemplary* exemplary = new Exemplary();
	exemplary->editionNumber = (rand() % 5) + 1;
	exemplary->libraryUbication = libraryUbications[rand() % (std::size(libraryUbications))];

	exemplary->bookID = book->modelID;
	book->exemplaries.push_back(exemplary);
	return exemplary;
}

Exemplary* ExemplaryFactory::CreateExemplary(int editionNumber, std::string libraryUbication, int bookModelId)
{
	Exemplary* exemplary = new Exemplary();
	exemplary->editionNumber = editionNumber;
	exemplary->libraryUbication = libraryUbication;
	exemplary->bookID = bookModelId;
	return exemplary;
}
