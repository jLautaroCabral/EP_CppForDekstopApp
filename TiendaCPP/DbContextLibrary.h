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
protected:
	DbContextLibrary();
	static DbContextLibrary* singleton_;

	
public:
	static DbContextLibrary* GetInstance();
	//      * Singletons should not be cloneable.
	DbContextLibrary(DbContextLibrary& other) = delete;
	//      * Singletons should not be assignable.
	void operator=(const DbContextLibrary&) = delete;

	DbTable<Loan> loanTable;
	DbTable<Loan> loanHistoryTable;
	DbTable<Partner> partnerTable;
	DbTable<Exemplary> exemplaryTable;
	DbTable<Book> bookTable;
	~DbContextLibrary();
	void FillDbContextData();
	static void PrintBooksDebugInfo();
};
#endif