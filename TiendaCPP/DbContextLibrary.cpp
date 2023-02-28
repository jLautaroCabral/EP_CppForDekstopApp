#include <iostream>
#include "DbContextLibrary.h"
#include "BookFactory.h"
#include "ExemplaryFactory.h"

DbContextLibrary::DbContextLibrary()
{
	FillDbContextData();
	PrintDebugInfo();
}

DbContextLibrary::~DbContextLibrary()
{
}

void DbContextLibrary::FillDbContextData()
{
	Book* bookExample = BookFactory::CreateRandomBook();
	bookTable.Add(bookExample);
	for (int i = 0; i < 2; i++)
	{
		Exemplary* exemplaryExample = ExemplaryFactory::CreateRandomExemplary();
		exemplaryTable.Add(exemplaryExample);
		exemplaryExample->bookID = bookExample->modelID;
	}

	bookExample = BookFactory::CreateRandomBook();
	bookTable.Add(bookExample);
	for (int i = 0; i < 1; i++)
	{
		Exemplary* exemplaryExample = ExemplaryFactory::CreateRandomExemplary();
		exemplaryTable.Add(exemplaryExample);
		exemplaryExample->bookID = bookExample->modelID;
	}

	// = new Book();
//bookExample->name = "Harry Potter";

//exemplaryExample->libraryUbication = "AAA";
// 
//exemplaryTable.Remove(*exemplaryExample);
//exemplaryTable.RemoveElementsWich([](Exemplary* const p) { return p->libraryUbication == "AAA"; }); // I AM A FUCKING GENIOUS
//exemplaryTable.Remove(exemplaryTable.GetAllItems());

//exemplaryTable.GetElementByID(0)->libraryUbication = "AAA";
//exemplaryTable.GetElementByID(1)->libraryUbication = "BBB";
//exemplaryTable.GetElementByID(2)->libraryUbication = "CCC";

//std::vector<Exemplary*> exemList = exemplaryTable.GetElementsWhich([](Exemplary* const ex) { return ex->libraryUbication == "AAA"; });
//exemList[0]->libraryUbication = "CCC";

//delete bookExample;


}

void DbContextLibrary::PrintDebugInfo()
{
	for (const Exemplary* item : exemplaryTable.GetAllItems())
	{
		printf_s("\n\n\n");
		printf_s("Exemplary data\n");
		printf_s("********************************************");
		printf_s("\n");
		printf_s(("ID: " + std::to_string(item->modelID)).c_str());
		printf_s("\n");
		printf_s(("Edition number: " + std::to_string(item->editionNumber)).c_str());
		printf_s("\n");
		printf_s(("Library ubication: " + item->libraryUbication).c_str());
		printf_s("\n");
		printf_s("Book data:                      ------------\n");
		printf_s("\n");
		printf_s(("Book ID: " + std::to_string(bookTable.GetElementByID(item->bookID)->modelID)).c_str());
		printf_s("\n");
		printf_s(("Book name: " + bookTable.GetElementByID(item->bookID)->name + " - " + bookTable.GetElementByID(item->bookID)->autor).c_str());
		
	}
}
