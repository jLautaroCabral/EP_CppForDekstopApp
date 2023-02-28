#pragma once
#include "Book.h"
#ifndef BOOK_FACTORY_H
#define BOOK_FACTORY_H
class BookFactory
{
	static const std::string autorNames[3];
	static const std::string booksNames[5];
private:
	
	static std::string CreateRandomISBNCode();
public:
	static Book* CreateRandomBook();
	static Book* CreateBook(std::string bookName, std::string authorName);
	static Book* CreateBook(std::string bookName, std::string authorName, std::string isbnCode);
};
#endif // !BOOK_FACTORY_H

