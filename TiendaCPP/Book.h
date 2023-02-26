#include <string>

#ifndef BOOK_H
#define BOOK_H
class Book
{
	std::string name;
	std::string ISBNcode;
	std::string autor;

	void AddBook();
	void ConsultExemplary();
	void LoanExemplary();
	void RegisterExemplary();
};
#endif