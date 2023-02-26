#include <string>
#include <list>
#include "Exemplary.h"

#ifndef PARTNER_H
#define PARTNER_H
class Partner
{
	std::string name;
	std::string lastName;
	std::string idNumber;
	std::string idNumber;
	int maxWithdrawalAmount;
	
	std::list<Exemplary*> withdrawnExemplaries;
	std::list<Exemplary*> loanedExemplaries;

	void CanApplyForALoan();
	void TryLoanExemplary();
	void ReturnExemplary();
};
#endif