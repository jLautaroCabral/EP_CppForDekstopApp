#include <string>
#include "Exemplary.h"
#include "Partner.h"
#include "DbModelItem.h"

#ifndef LOAN_H
#define LOAN_H
class Loan : public DbModelItem
{
public:
	Loan();
	~Loan();

	Exemplary* exemplary;
	Partner* partner;
	//TODO: add loan date
	//TimeSpan loanDate;
	time_t* loanDate;
};
#endif