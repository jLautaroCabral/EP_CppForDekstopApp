#include <vector>
#include <list>
#include <concepts>
#include "DbModelItem.h"
#include "Loan.h"

#ifndef DB_TABLE_EXAMPLE_H
#define DB_TABLE_EXAMPLE_H

class DbTableExample
{
private:
	std::vector<Loan*> listItems;
public:
	DbTableExample();
	~DbTableExample();

	void Get();
	const std::vector<Loan*> GetAllItems() const;
	void Add(Loan itemToAdd);
	void Remove(Loan itemToRemove);
};

// TODO: Move this to DbTable.cpp

#endif