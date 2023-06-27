#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <random>
#include <thread>
#include <windows.h>

#include "PairedSwords.h"
#include "Spear.h"
#include "Bow.h"

#include "LeatherArmor.h"
#include "ChainMail.h"
#include "Lats.h"

#include "RegularGladiator.h"
#include "HeavyGladiator.h"
#include "LightWeightGladiator.h"

#include "PNGstConsoleIMage.h"
#include "Animations.h"

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

IGladiator* gladiatorBuilder(int32_t gladiatorType, int32_t weaponType, int32_t armorType, std::string name, std::mt19937& mt) {
	IGladiator* result{};
	IWeapon* weapon{};
	IArmor* armor{};	
	switch (armorType)
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
	switch (weaponType)
	{
	case 1:
		weapon = new Bow(8, "Artemida`s tear Bow", mt);
		break;
	case 2:
		weapon = new PairedSwords(10, "Cerberus fangs Paired swords", mt);
		break;
	case 3:
		weapon = new Spear(14, "Achilles`s Spear");
		break;
	}
	switch (gladiatorType)
	{
	case 1:
		result = new RegularGladiator(weapon, armor, 60, name);
		break;
	case 2:
		result = new HeavyGladiator(weapon, armor, 70, name);
		break;
	case 3:
		result = new LightWeightGladiator(weapon, armor, 50, name);
		break;
	}

	return result;
}

int main()
{
	std::random_device rt;
	std::mt19937 mt(rt());

	system("color F0");

	IGladiator* gladiator1{};
	IGladiator* gladiator2{};

	std::cout << "Would you like to use prepared warriors? 0/1:";
	bool rand(getValue(0, 1));
	system("cls");
	if (rand) {
		std::uniform_int_distribution<int> dist{std::uniform_int_distribution<int>(1, 3)};
		gladiator1 = gladiatorBuilder(dist(mt), dist(mt), dist(mt), "Gladiator 1", mt);
		gladiator2 = gladiatorBuilder(dist(mt), dist(mt), dist(mt), "Gladiator 2", mt);
	}
	else {

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
		int32_t armor{ getValue(1, 3) };

		std::cout << endl;
		std::cout << "1 - Bow" << endl;
		std::cout << "2 - Spear" << endl;
		std::cout << "3 - Paired Swords" << endl;
		int32_t weapon{ getValue(1, 3) };

		std::string name{};
		std::cout << "Input name of first gladiator:";
		std::cin.ignore();
		getline(std::cin, name);

		gladiator1 = gladiatorBuilder(gladiator, weapon, armor, name, mt);

		std::cout << "Gladiator 2" << endl;
		std::cout << "1 - Regular" << endl;
		std::cout << "2 - Heavy" << endl;
		std::cout << "3 - LightWeight" << endl;
		gladiator = getValue(1, 3);
		std::cout << endl;
		std::cout << "1 - LeatherArmor" << endl;
		std::cout << "2 - Lats" << endl;
		std::cout << "3 - ChainMail" << endl;
		armor = getValue(1, 3);

		std::cout << endl;
		std::cout << "1 - Bow" << endl;
		std::cout << "2 - Spear" << endl;
		std::cout << "3 - Paired Swords" << endl;
		weapon = getValue(1, 3);

		std::cout << "Input name of second gladiator:";
		std::cin.ignore();
		getline(std::cin, name);

		gladiator2 = gladiatorBuilder(gladiator, weapon, armor, name, mt);

	}

	gladiator2->flip();
	std::cout << "\n\n\nBATTLE BEGINS!\n\n\n";
	gladiator1->setPosition(200, 300);
	gladiator2->setPosition(700, 300);
	while (*gladiator1 && *gladiator2) {
		std::cout << std::endl << *gladiator1 << *gladiator2 << std::endl;
		
		gladiator1->setPosition(400, 300);
		gladiator1->draw();
		gladiator2->draw();
		gladiator1->dealDamage(*gladiator2);		
		if (*gladiator2) {
			gladiator1->setPosition(200, 300);		
			system("cls");
			gladiator1->draw();
			gladiator2->draw();
			this_thread::sleep_for(std::chrono::milliseconds(300));
			system("cls");
			gladiator2->setPosition(500, 300);
			gladiator1->draw();
			gladiator2->draw();
			gladiator2->dealDamage(*gladiator1);
			gladiator2->setPosition(700, 300);
			if (!*gladiator1)
				break;
		}		
		else {
			break;
		}
		
		system("cls");
		gladiator1->draw();
		gladiator2->draw();
		this_thread::sleep_for(std::chrono::milliseconds(300));
		system("cls");
		
		
	}

	std::cout << "THE END!";
	delete gladiator1;
	delete gladiator2;
	return 0;
}

