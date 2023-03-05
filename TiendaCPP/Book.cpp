#include "Book.h"

Book::Book()
{
	name = "Example Name";
	ISBNcode = "ISBN - Example";
	autor = "Example Author";
}

Book::~Book()
{
}

bool Book::HaveExemplaries() const
{
    return !exemplaries.empty();
}

void Book::AddExemplary(Exemplary* exemplaryToAdd)
{
	exemplaries.push_back(exemplaryToAdd);
}

Exemplary* Book::LoanExemplary(Exemplary* exemplaryToLoan)
{
	auto resultIterator = std::find_if(begin(exemplaries), end(exemplaries), [&](Exemplary* const p) { return *p == *exemplaryToLoan; });
	if (resultIterator == end(exemplaries))
	{
		throw;
	}
	Exemplary* resultExemplary = *resultIterator;
	// TODO: Improve this
	exemplaries.erase(std::remove(exemplaries.begin(), exemplaries.end(), exemplaryToLoan));

    return resultExemplary;
}

void Book::RegisterReturnOfExemplary(Exemplary* exemplary)
{
	exemplaries.push_back(exemplary);
}
