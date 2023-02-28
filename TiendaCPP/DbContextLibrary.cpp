#include <iostream>
#include "DbContextLibrary.h"

DbContextLibrary::DbContextLibrary()
{
	Example();
}

DbContextLibrary::~DbContextLibrary()
{
}

void DbContextLibrary::Example()
{
	Book* bookExample = new Book();
	bookExample->name = "Harry Potter";

	Exemplary* exemplaryExample;

	std::vector<Exemplary*> exemplaries;
	std::vector<Exemplary> exemplariesInDB;
	for (int i = 0; i < 3; i++)
	{
		exemplaryExample = new Exemplary();
		// Crud test
		exemplaryTable.Add(exemplaryExample);
		exemplaryExample->bookID = 0;
	}

	//exemplaryExample->libraryUbication = "AAA";
	// 
	//exemplaryTable.Remove(*exemplaryExample);
	//exemplaryTable.RemoveElementsWich([](Exemplary* const p) { return p->libraryUbication == "AAA"; }); // I AM A FUCKING GENIOUS
	//exemplaryTable.Remove(exemplaryTable.GetAllItems());

	exemplaryTable.GetElementByID(0)->libraryUbication = "AAA";
	exemplaryTable.GetElementByID(1)->libraryUbication = "BBB";
	exemplaryTable.GetElementByID(2)->libraryUbication = "CCC";

	std::vector<Exemplary*> exemList = exemplaryTable.GetElementsWhich([](Exemplary* const ex) { return ex->libraryUbication == "AAA"; });
	exemList[0]->libraryUbication = "CCC";

	delete bookExample;

	for (const Exemplary* item : exemplaryTable.GetAllItems())
	{
		printf_s("\n");
		printf_s("Exemplary data: ----------- ********");
		printf_s("\n");
		printf_s(std::to_string(item->modelID).c_str());
		printf_s("\n");
		printf_s(item->libraryUbication.c_str());
		printf_s("\n");
		printf_s("Book data: ----------------");
		printf_s("\n");
		printf_s("---------------------------");
	}
}
