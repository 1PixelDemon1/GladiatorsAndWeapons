#include <iostream>
#include <random>
#include <thread>

#include "PairedSwords.h"
#include "Spear.h"
#include "Bow.h"

#include "LeatherArmor.h"
#include "ChainMail.h"
#include "Lats.h"

#include "RegularGladiator.h"
#include "HeavyGladiator.h"
#include "LightWeightGladiator.h"

using namespace std;

int32_t getValue(int32_t from, int32_t to) {
	int32_t res;
	std::cin >> res;
	while (std::cin.fail() || res < from || res > to)
	{
		std::cin.clear();
		std::cin.ignore();
		std::cin >> res;
	}
	return res;
}

int main()
{
	std::random_device rt;
	std::mt19937 mt(rt());

#define PRE_LOADED_

#ifdef PRE_LOADED
	IGladiator* gladiator1 = new HeavyGladiator(new Spear(15, "God`s spear"), new LeatherArmor(7, 50, "Regular leather armor"), 60, "Wulfus");
	IGladiator* gladiator2 = new RegularGladiator(new PairedSwords(12, "Cerberus fangs", mt), new Lats(7, 50, "Regular lats", mt), 60, "Hector");
#else


	IGladiator* gladiator1{};
	IGladiator* gladiator2{};

	std::cout << " Welcome to the next gladiator confrontation! Let's take a look at our participants!" << std::endl;

	std::cout << "Gladiator 1" << endl;
	std::cout << "1 - Regular" << endl;
	std::cout << "2 - Heavy" << endl;
	std::cout << "3 - LightWeight" << endl;
	int32_t gladiator{ getValue(1, 3) };
	std::cout << endl;
	std::cout << "1 - LeatherArmor" << endl;
	std::cout << "2 - Lats" << endl;
	std::cout << "3 - ChainMail" << endl;
	IArmor* armor{};
	
	switch (getValue(1, 3))
	{
	case 1:
		armor = new LeatherArmor(7, 60, "Leather Armor");
		break;
	case 2:
		armor = new Lats(8, 50, "Lats", mt);
		break;
	case 3:
		armor = new ChainMail (7, 55, "ChainMail", mt);
		break;	
	}
	std::cout << endl;
	std::cout << "1 - Bow" << endl;
	std::cout << "2 - Spear" << endl;
	std::cout << "3 - Paired Swords" << endl;
	IWeapon* weapon{};
	
	switch (getValue(1, 3))
	{
	case 1:
		weapon = new Bow(12, "Artemida`s tear Bow", mt);
		break;
	case 2:
		weapon = new PairedSwords(10, "Cerberus fangs Paired swords", mt);
		break;
	case 3:
		weapon = new Spear(14, "Achilles`s Spear");
		break;	
	}
	std::string name{};
	std::cout << "Input name of first gladiator:";
	std::cin.ignore();
	getline(std::cin, name);
	switch (gladiator)
	{
	case 1:
		gladiator1 = new RegularGladiator(weapon, armor, 60, name);
		break;
	case 2:
		gladiator1 = new HeavyGladiator(weapon, armor, 60, name);
		break;
	case 3:
		gladiator1 = new LightWeightGladiator(weapon, armor, 60, name);
		break;
	}

	std::cout << "Gladiator 2" << endl;
	std::cout << "1 - Regular" << endl;
	std::cout << "2 - Heavy" << endl;
	std::cout << "3 - LightWeight" << endl;
	gladiator = getValue(1, 3);
	std::cout << endl;
	std::cout << "1 - LeatherArmor" << endl;
	std::cout << "2 - Lats" << endl;
	std::cout << "3 - ChainMail" << endl;

	switch (getValue(1, 3))
	{
	case 1:
		armor = new LeatherArmor(7, 60, "Leather Armor");
		break;
	case 2:
		armor = new Lats(8, 50, "Lats", mt);
		break;
	case 3:
		armor = new ChainMail(7, 55, "ChainMail", mt);
		break;
	}
	std::cout << endl;
	std::cout << "1 - Bow" << endl;
	std::cout << "2 - Spear" << endl;
	std::cout << "3 - Paired Swords" << endl;
;

	switch (getValue(1, 3))
	{
	case 1:
		weapon = new Bow(12, "Artemida`s tear Bow", mt);
		break;
	case 2:
		weapon = new PairedSwords(10, "Cerberus fangs Paired swords", mt);
		break;
	case 3:
		weapon = new Spear(14, "Achilles`s Spear");
		break;
	}

	std::cout << "Input name of second gladiator:";
	std::cin.ignore();
	getline(std::cin, name);
	switch (gladiator)
	{
	case 1:
		gladiator2 = new RegularGladiator(weapon, armor, 60, name);
		break;
	case 2:
		gladiator2 = new HeavyGladiator(weapon, armor, 60, name);
		break;
	case 3:
		gladiator2 = new LightWeightGladiator(weapon, armor, 60, name);
		break;
	}

#endif // PRE_LOADED
	std::cout << "\n\n\nBATTLE BEGINS!\n\n\n";

	while (*gladiator1 && *gladiator2) {
		std::cout << std::endl << *gladiator1 << *gladiator2 << std::endl;
		
		gladiator1->dealDamage(*gladiator2);
		
		if(*gladiator2)
			gladiator2->dealDamage(*gladiator1);

		this_thread::sleep_for(std::chrono::milliseconds(1500));
	}

	std::cout << "THE END!";
	delete gladiator1;
	delete gladiator2;
	return 0;
}

