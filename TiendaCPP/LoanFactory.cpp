#include "LoanFactory.h"

Loan* LoanFactory::CreateLoan(Partner* partner, Exemplary* exemplary)
{
	Loan* loan = new Loan();
	loan->partner = partner;
	loan->exemplary = exemplary;
	loan->loanDate = new time_t();

	// TODO: Analize this
	//std::chrono::system_clock::time_point* time = new std::chrono::system_clock::time_point();
	//*time = std::chrono::system_clock::now();
	auto currentTime = std::chrono::system_clock::now();
	*loan->loanDate = std::chrono::system_clock::to_time_t(currentTime);

	return loan;
}
