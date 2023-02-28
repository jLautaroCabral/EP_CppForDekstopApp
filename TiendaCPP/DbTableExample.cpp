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

Loan* DbTableExample::GetElementByID(int id)
{
	auto resultIterator = std::find_if(begin(listItems), end(listItems), [&](Loan* const& p) { return p->modelID == id; });

	if (resultIterator != end(listItems))
	{
		return *resultIterator;
	}
	return nullptr;
}

const std::vector<Loan*> DbTableExample::GetAllItems() const
{
    return std::vector<Loan*>();
}

const std::vector<Loan*> DbTableExample::GetElementsWich(Predicade func)
{
	std::vector<Loan*> vectorToReturn;
	std::vector<Loan*>::iterator resultIterator = std::find_if(begin(listItems), end(listItems), [&](Loan* const& p) { return func(p); });

	while (resultIterator != end(listItems))
	{
		vectorToReturn.push_back(*resultIterator);
		resultIterator = std::find_if(resultIterator, end(listItems), [&](Loan* const& p) { return func(p); });
	}

	return vectorToReturn;
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
	listItems.erase(
		std::remove_if(listItems.begin(), listItems.end(),
			[&](Loan* const& p) { return p->modelID == itemToRemove.modelID; }),
		listItems.end());
}
