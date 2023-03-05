#include <string>
#include "Loan.h"
#include "Partner.h"
#include "Exemplary.h"
#include <iostream>
#include <chrono>

#ifndef LOAN_FACTORY_H
#define LOAN_FACTORY_H
class LoanFactory
{
public:
	static Loan* CreateLoan(Partner* partner, Exemplary* exemplary, LoanType type);
};
#endif // !PARTNER_FACTORY_H