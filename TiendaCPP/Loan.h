#include <string>
#include "Exemplary.h"
#include "Partner.h"
#include "DbModelItem.h"

#ifndef LOAN_H
#define LOAN_H
class Loan : public DbModelItem
{
	Exemplary exemplary;
	Partner partner;
	//TODO: add loan date
	//TimeSpan loanDate;
public:
	Loan();
	~Loan();
};
#endif