#include <iostream>
#include "DbContextLibrary.h"
#include "BookFactory.h"
#include "ExemplaryFactory.h"

DbContextLibrary::DbContextLibrary()
{
	FillDbContextData();
}

DbContextLibrary::~DbContextLibrary()
{
}

DbContextLibrary* DbContextLibrary::singleton_ = nullptr;

DbContextLibrary* DbContextLibrary::GetInstance()
{
	/**
	 * This is a safer way to create an instance. instance = new Singleton is
	 * dangeruous in case two instance threads wants to access at the same time
	 */
	if (singleton_ == nullptr) {
		singleton_ = new DbContextLibrary();
	}
	return singleton_;
}


void DbContextLibrary::FillDbContextData()
{
	// Fill Books and Exemplaries
	for (int i = 0; i < 5; i++)
	{
		Book* bookExample = BookFactory::CreateRandomBook();
		bookTable.Add(bookExample);

		for (int j = 0; j < (rand() % 5) + 1; j++)
		{
			Exemplary* exemplaryExample = ExemplaryFactory::CreateRandomExemplary(bookExample);
			exemplaryTable.Add(exemplaryExample);
		}
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

// TODO: UPGRADE
void DbContextLibrary::PrintBooksDebugInfo()
{
	printf_s("*** START: Print book debug info:\n");
	for (const Book* book : GetInstance()->bookTable.GetAllItems())
	{
		printf_s("\n");
		printf_s("---------------------------------------");
		printf_s("\n");
		printf_s(("Book ID: " + std::to_string(book->modelID)).c_str());
		printf_s("\n");
		printf_s(("Book name: " + book->name + " - " + book->autor).c_str());
		printf_s("\n");
		/*
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
	*/	
	}
	printf_s("*** END: Print book debug info:\n");
}
