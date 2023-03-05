#include <string>
#include <list>
#include "Exemplary.h"
#include "DbModelItem.h"

#ifndef PARTNER_H
#define PARTNER_H
class Partner : public DbModelItem
{
public:
	std::string name;
	std::string lastName;
	std::string idNumber;
	int maxWithdrawalAmount;
	
	//std::list<Exemplary*> withdrawnExemplaries;
	std::list<Exemplary*> loanedExemplaries;

	bool CanApplyForALoan();
	void LoanExemplary(Exemplary* exemplaryToLoan);
	Exemplary* ReturnExemplary(Exemplary* exemplaryToLoan);

	static bool IsPartnerVIP(Partner* partnerInstance);
};
#endif