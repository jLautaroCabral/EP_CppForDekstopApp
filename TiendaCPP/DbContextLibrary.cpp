#include <iostream>
#include "DbContextLibrary.h"
#include "BookFactory.h"
#include "ExemplaryFactory.h"
#include "PartnerFactory.h"
#include "LoanFactory.h"

DbContextLibrary::DbContextLibrary()
{
	FillDbContextData();
}

DbContextLibrary::~DbContextLibrary()
{
}

DbContextLibrary* DbContextLibrary::singleton_ = nullptr;

DbContextLibrary* DbContextLibrary::GetInstance()
{
	/**
	 * This is a safer way to create an instance. instance = new Singleton is
	 * dangeruous in case two instance threads wants to access at the same time
	 */
	if (singleton_ == nullptr) {
		singleton_ = new DbContextLibrary();
	}
	return singleton_;
}


void DbContextLibrary::FillDbContextData()
{
	const int amountOfBooksToGenerate = 10;
	const int amountOfExemplariesPerBookToGenerate = 3;
	const int amountOfPartnersToGenerate = 8;
	const int amountOfLoansToGenerate = 2;

	// Fill Books and Exemplaries
	for (int i = 0; i < amountOfBooksToGenerate; i++)
	{
		Book* bookSample = BookFactory::CreateRandomBook();
		bookTable.Add(bookSample);

		for (int j = 0; j < amountOfExemplariesPerBookToGenerate; j++)
		{
			Exemplary* exemplarySample = ExemplaryFactory::CreateRandomExemplary(bookSample);
			exemplaryTable.Add(exemplarySample);
			bookSample->AddExemplary(exemplarySample);
		}
	}

	// Fill Partners and its Exampleries
	for (int i = 0; i < amountOfPartnersToGenerate; i++)
	{
		Partner* partnerSample;
		if (i % 2 == 0)
		{
			partnerSample = PartnerFactory::CreateRandomPartner();
		}
		else
		{
			partnerSample = PartnerFactory::CreateRandomPartnerVIP();
		}

		partnerTable.Add(partnerSample);
	}

	// Fill Partners and its Exampleries
	for (int i = 0; i < amountOfLoansToGenerate; i++)
	{
		Partner* randomPartner = partnerTable.GetAllItems()[i];
		Book* bookOfExemplary = bookTable.GetAllItems()[i];
		Exemplary* randomExemplary = bookOfExemplary->exemplaries[0];

		randomExemplary = bookOfExemplary->LoanExemplary(randomExemplary);
		randomPartner->LoanExemplary(randomExemplary);

		Loan* loanSample = LoanFactory::CreateLoan(randomPartner, randomExemplary, LoanType::Withdrawal);
		loanTable.Add(loanSample);
		loanHistoryTable.Add(loanSample);
	}
}

// TODO: JUST FOR DEBUGGING
void DbContextLibrary::PrintBooksDebugInfo()
{
	printf_s("*** START: Print book debug info:\n");
	for (const Book* book : GetInstance()->bookTable.GetAllItems())
	{
		printf_s("\n");
		printf_s("---------------------------------------");
		printf_s("\n");
		printf_s(("Book ID: " + std::to_string(book->modelID)).c_str());
		printf_s("\n");
		printf_s(("Book name: " + book->name + " - " + book->autor).c_str());
		printf_s("\n");
	}
	printf_s("*** END: Print book debug info:\n");
}
