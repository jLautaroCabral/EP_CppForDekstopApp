#include "Partner.h"
#include "PartnerVIP.h"

bool Partner::CanApplyForALoan()
{
	return std::size(loanedExemplaries) <= maxWithdrawalAmount;
}

bool Partner::LoanExemplary(Exemplary* exemplaryToLoan)
{
	if (CanApplyForALoan())
	{
		loanedExemplaries.push_back(exemplaryToLoan);
		return true;
	}
	else
	{
		return false;
	}
}

Exemplary* Partner::ReturnExemplary(Exemplary* exemplaryToLoan)
{
	auto resultIterator = std::find_if(begin(loanedExemplaries), end(loanedExemplaries), [&](Exemplary* const p) { return *p == *exemplaryToLoan; });
	if (resultIterator == end(loanedExemplaries))
	{
		throw;
	}
	Exemplary* resultExemplary = *resultIterator;
	// TODO: Improve this
	loanedExemplaries.erase(std::remove(loanedExemplaries.begin(), loanedExemplaries.end(), exemplaryToLoan));

	return resultExemplary;
}

// TODO: I thinks makes more sende move this method to PartnerVIP class
bool Partner::IsPartnerVIP(Partner* partnerInstance)
{
	PartnerVIP* partnerSelectedVIP = dynamic_cast<PartnerVIP*>(partnerInstance);
    return partnerSelectedVIP != nullptr;
}
