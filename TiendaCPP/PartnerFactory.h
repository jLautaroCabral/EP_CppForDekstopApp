#include <string>
#include "Partner.h"
#include "PartnerVIP.h"

#ifndef PARTNER_FACTORY_H
#define PARTNER_FACTORY_H
class PartnerFactory
{
private:
	static const std::string names[10];
	static const std::string lastNames[10];
public:
	static Partner* CreateRandomPartner();
	static PartnerVIP* CreateRandomPartnerVIP();
	//static Exemplary* CreateRandomExemplary(Book* book);
	//static Exemplary* CreateExemplary();
};
#endif // !PARTNER_FACTORY_H