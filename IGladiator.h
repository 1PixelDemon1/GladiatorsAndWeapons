#pragma once

#include "IWeapon.h"
#include "IArmor.h"
#include <cstdint>
#include <iostream>


class IGladiator {
private:
	int32_t health;
	std::string name;
	IWeapon& weapon;
	IArmor& armor;

public:

	IGladiator(IWeapon* weapon, IArmor* armor, int32_t health = 100, std::string name = "Gladiator") : 
		weapon{ *weapon }, armor{ *armor }, health{ health }, name{name} {}

	virtual void dead() = 0;

	virtual void win() = 0;

	virtual int32_t getHealth() { return health; }

	virtual void dealDamage(IGladiator& gladiator) {
		int32_t tempDamage{ weapon.damage() };
		int32_t tempArmor{ gladiator.armor.value() };

		gladiator.health -= tempArmor / tempDamage * tempDamage;
		armor.dealDamage(tempDamage);
		if (gladiator.health <= 0) {
			gladiator.dead();
			win();
		}
	}

	virtual ~IGladiator() {
		if(&weapon) delete[] &weapon;
		if(&armor) delete[] &armor;
	}

};