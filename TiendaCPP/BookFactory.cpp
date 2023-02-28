#include "BookFactory.h"
#include <cstdlib>

const std::string BookFactory::autorNames[3] = { "Charles Dickens", "Julio Verne", "Oscar Wilde" };
const std::string BookFactory::booksNames[5] = { "Harry Potter", "Mr. Sandman", "El Se�or de los Anillos", "El C�digo da Vinc", "Crep�sculo"};

//MainWindowController* MainWindowController::singleton_ = nullptr;

std::string BookFactory::GetRandomISBNCode()
{
	return
		std::to_string(rand() % 999) + "-" +
		std::to_string(rand() % 999) + "-" +
		std::to_string(rand() % 99999) + "-" +
		std::to_string(rand() % 9) + "-" +
		std::to_string(rand() % 9);
}

Book* BookFactory::GetRandomBook()
{
	Book* book = new Book();
	book->modelID = 0;
	book->name = booksNames[rand() % (std::size(booksNames) - 1)];
	book->autor = autorNames[rand() % (std::size(autorNames) - 1)];
	book->ISBNcode = GetRandomISBNCode();
    return book;
}

Book* BookFactory::CreateBook(std::string bookName, std::string authorName)
{
	Book* book = new Book();
	book->modelID = 0;
	book->name = bookName;
	book->autor = authorName;
	book->ISBNcode = GetRandomISBNCode();
	return book;
}

Book* BookFactory::CreateBook(std::string bookName, std::string authorName, std::string isbnCode)
{
	Book* book = new Book();
	book->modelID = 0;
	book->name = bookName;
	book->autor = authorName;
	book->ISBNcode = isbnCode;
	return book;
}
