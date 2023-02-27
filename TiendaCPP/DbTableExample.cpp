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
	//std::list<Loan*>::iterator it = std::find_if(std::begin(listItems), std::end(listItems),
	//	[&](Loan* const& p) { return p->modelID == itemToRemove.modelID; });

	// Se encontró el item
	listItems.remove_if([&](Loan* const& p) { return p->modelID == itemToRemove.modelID; });
}
