#include "DbTable.h"
#include "Loan.h"
#include "DbModelItem.h"


#ifndef DB_CONTEXT_LIBRARY_H
#define DB_CONTEXT_LIBRARY_H
class DbContextLibrary
{
	DbTable<Loan> loanList;
public:
	DbContextLibrary();
	~DbContextLibrary();
	void Example();
};
#endif