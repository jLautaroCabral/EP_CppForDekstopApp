#include "BookFactory.h"
#include <cstdlib>

const std::string BookFactory::autorNames[3] = { "Charles Dickens", "Julio Verne", "Oscar Wilde" };
const std::string BookFactory::booksNames[5] = { "Harry Potter", "Mr. Sandman", "El Señor de los Anillos", "El Código da Vinc", "Crepúsculo"};

//MainWindowController* MainWindowController::singleton_ = nullptr;

std::string BookFactory::CreateRandomISBNCode()
{
	return
		std::to_string(rand() % 999) + "-" +
		std::to_string(rand() % 999) + "-" +
		std::to_string(rand() % 99999) + "-" +
		std::to_string(rand() % 9) + "-" +
		std::to_string(rand() % 9);
}

Book* BookFactory::CreateRandomBook()
{
	Book* book = new Book();
	book->modelID = -1;
	book->name = booksNames[rand() % (std::size(booksNames) - 1)];
	book->autor = autorNames[rand() % (std::size(autorNames) - 1)];
	book->ISBNcode = CreateRandomISBNCode();
    return book;
}

Book* BookFactory::CreateBook(std::string bookName, std::string authorName)
{
	Book* book = new Book();
	book->modelID = -1;
	book->name = bookName;
	book->autor = authorName;
	book->ISBNcode = CreateRandomISBNCode();
	return book;
}

Book* BookFactory::CreateBook(std::string bookName, std::string authorName, std::string isbnCode)
{
	Book* book = new Book();
	book->modelID = -1;
	book->name = bookName;
	book->autor = authorName;
	book->ISBNcode = isbnCode;
	return book;
}
