#include "Partner.h"
#include "PartnerVIP.h"

// TODO: I thinks makes more sende move this method to PartnerVIP class
bool Partner::IsPartnerVIP(Partner* partnerInstance)
{
	PartnerVIP* partnerSelectedVIP = dynamic_cast<PartnerVIP*>(partnerInstance);
    return partnerSelectedVIP != nullptr;
}
