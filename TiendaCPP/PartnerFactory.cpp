#include "PartnerFactory.h"

const std::string PartnerFactory::names[10] = {
	"Charles",
	"Nicolas",
	"Marketa",
	"Lautaro",
	"Milagros",
	"Ignacio",
	"Luciano",
	"Ivan",
	"Agustina",
	"Emma"
};
const std::string PartnerFactory::lastNames[10] = {
	"Potter",
	"Jaroslav",
	"Vinci",
	"Angelo",
	"Deccoco",
	"Yed",
	"Magnate",
	"Demaio",
	"Cabral",
	"Meyer"
};

Partner* PartnerFactory::CreatePartner(std::string name, std::string lastName)
{
	Partner* partner = new Partner();
	partner->name = name;
	partner->lastName = lastName;
	partner->idNumber = std::to_string(rand() % 999) + "-" + std::to_string(rand() % 99) + "-" + std::to_string(rand() % 999);
	partner->maxWithdrawalAmount = 1;
	return partner;
}

PartnerVIP* PartnerFactory::CreatePartnerVIP(std::string name, std::string lastName)
{
	PartnerVIP* partner = new PartnerVIP();
	partner->name = name;
	partner->lastName = lastName;
	partner->idNumber = std::to_string(rand() % 999) + "-" + std::to_string(rand() % 99) + "-" + std::to_string(rand() % 999);
	partner->maxWithdrawalAmount = 3;
	partner->monthlyFee = 100;
	return partner;
}

Partner* PartnerFactory::CreateRandomPartner()
{
	Partner* partner = new Partner();
	partner->name = names[rand() % (std::size(names))];;
	partner->lastName = lastNames[rand() % (std::size(lastNames))];;
	partner->idNumber = std::to_string(rand() % 999) + "-" + std::to_string(rand() % 99) + "-" + std::to_string(rand() % 999);
	partner->maxWithdrawalAmount = 1;
    return partner;
}

PartnerVIP* PartnerFactory::CreateRandomPartnerVIP()
{
	PartnerVIP* partner = new PartnerVIP();
	partner->name = names[rand() % (std::size(names))];;
	partner->lastName = lastNames[rand() % (std::size(lastNames))];;
	partner->idNumber = std::to_string(rand() % 999) + "-" + std::to_string(rand() % 99) + "-" + std::to_string(rand() % 999);
	partner->maxWithdrawalAmount = 3;
	partner->monthlyFee = 100;
    return partner;
}