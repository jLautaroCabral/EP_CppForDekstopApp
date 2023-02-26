#include "DbTableExample.h"

DbTableExample::DbTableExample()
{
}

DbTableExample::~DbTableExample()
{
}

void DbTableExample::Get()
{
}

const std::list<Loan*> DbTableExample::GetAllItems() const
{
    return std::list<Loan*>();
}

void DbTableExample::Add(Loan itemToAdd)
{
	listItems.push_back(&itemToAdd);
}

void DbTableExample::Remove(Loan itemToRemove)
{
}
