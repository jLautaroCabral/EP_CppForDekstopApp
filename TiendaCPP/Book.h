#include <string>
#include "DbModelItem.h"

#ifndef BOOK_H
#define BOOK_H
class Book : public DbModelItem
{
public:
	std::string name;
	std::string ISBNcode;
	std::string autor;

	Book();
	~Book();

	void AddBook();
	void ConsultExemplary();
	void LoanExemplary();
	void RegisterExemplary();
};
#endif