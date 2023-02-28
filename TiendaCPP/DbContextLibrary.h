#include "DbTable.h"
#include "DbModelItem.h"
#include "Loan.h"
#include "Partner.h"
#include "Exemplary.h"
#include "Book.h"

#ifndef DB_CONTEXT_LIBRARY_H
#define DB_CONTEXT_LIBRARY_H
class DbContextLibrary
{
	DbTable<Loan> loanTable;
	DbTable<Partner> partnerTable;
	DbTable<Exemplary> exemplaryTable;
	DbTable<Book> bookList;
public:
	DbContextLibrary();
	~DbContextLibrary();
	void FillDbContextData();
	void PrintDebugInfo();
};
#endif