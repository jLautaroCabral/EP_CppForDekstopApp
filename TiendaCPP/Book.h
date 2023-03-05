#include <string>
#include <vector>
#include "DbModelItem.h"
#include "Exemplary.h"

#ifndef BOOK_H
#define BOOK_H
class Book : public DbModelItem
{
	friend class BookFactory;
private:
	Book();
public:
	~Book();

	std::string name;
	std::string ISBNcode;
	std::string autor;
	std::vector<Exemplary*> exemplaries;
	
	bool HaveExemplaries() const;
	void AddExemplary(Exemplary* exemplaryToAdd);
	Exemplary* LoanExemplary(Exemplary* exemplaryToLoan);
	void RegisterReturnOfExemplary(Exemplary* exemplary);
};
#endif