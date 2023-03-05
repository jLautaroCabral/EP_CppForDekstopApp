#include "BookFactory.h"
#include <cstdlib>

const std::string BookFactory::autorNames[10] = {
	"Charles Dickens",
	"Julio Verne",
	"Oscar Wilde",
	"Julio Cortazar",
	"Ken Follett",
	"Fiodor Dostoyevski",
	"Isaac asimov",
	"Stephen King",
	"J.R.R.Tolkien",
	"J.K.Rowling"
};
const std::string BookFactory::booksNames[10] = {
	"Harry Potter",
	"Mr. Sandman",
	"El Senior de los Anillos",
	"El Codigo da Vinci",
	"Crepusculo",
	"Luces de bohemia",
	"100 anios de Soledad",
	"La casa de los espiritus",
	"Preludio a la fundacion",
	"Las almas muertas"
};

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
	book->name = booksNames[rand() % (std::size(booksNames))];
	book->autor = autorNames[rand() % (std::size(autorNames))];
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
