#include "Partner.h"
#include "PartnerVIP.h"

bool Partner::CanApplyForALoan()
{
	return std::size(loanedExemplaries) < maxWithdrawalAmount;
}

void Partner::LoanExemplary(Exemplary* exemplaryToLoan)
{
	loanedExemplaries.push_back(exemplaryToLoan);
}

Exemplary* Partner::ReturnExemplary(Exemplary* exemplaryToLoan)
{
	auto resultIterator = std::find_if(begin(loanedExemplaries), end(loanedExemplaries), [&](Exemplary* const p) { return *p == *exemplaryToLoan; });
	if (resultIterator == end(loanedExemplaries))
	{
		return nullptr;
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
