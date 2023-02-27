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
	for (int i = 0; i < 3; i++)
	{
		exemplaryExample = new Exemplary();
		// Crud test
		exemplaryTable.Add(exemplaryExample);
		exemplaryExample->book = *bookExample;
	}
	exemplaryExample->libraryUbication = "AAA";
	//exemplaryTable.Remove(*exemplaryExample);
	exemplaryTable.RemoveItemsWich([](Exemplary* const p) { return p->libraryUbication == "AAA"; }); // I AM A FUCKING GENIOUS
	exemplaryTable.Remove(exemplaryTable.GetAllItems());
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
		printf_s(item->book.name.c_str());
		printf_s("\n");
		printf_s(item->book.autor.c_str());
		printf_s("\n");
		printf_s(item->book.ISBNcode.c_str());
		printf_s("\n");
		printf_s("---------------------------");
	}
}
