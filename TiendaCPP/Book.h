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
	std::string name;
	std::string ISBNcode;
	std::string autor;
	std::vector<Exemplary*> exemplaries;

	~Book();

	//void AddBook();
	void ConsultExemplary();
	void LoanExemplary();
	void RegisterExemplary();
};
#endif