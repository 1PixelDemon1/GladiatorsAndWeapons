#pragma once

#include "IWeapon.h"
#include "IArmor.h"
#include <cstdint>
#include <iostream>


class IGladiator {
protected:
	int32_t health;
	std::string name;
	IWeapon& weapon;
	IArmor& armor;

	int32_t getDamage() {
		return weapon.baseDamage;
	}
	int32_t getDefense() {
		return armor.defense;
	}

	void setDamage(int32_t damage) {
		weapon.baseDamage = damage;
	}

	void setDefense(int32_t defense) {
		armor.defense = defense;
	}

public:

	IGladiator(IWeapon* weapon, IArmor* armor, int32_t health = 100, std::string name = "Gladiator") : weapon{ *weapon }, armor{ *armor }, health{ health }, name{name} {}

	virtual void dead()  = 0;

	virtual void win()  = 0;

	virtual int32_t getHealth()  { return health; }

	virtual void dealDamage(IGladiator& gladiator) {
		int32_t tempDamage{ weapon.damage() };
		int32_t tempArmor{ gladiator.armor.value()};
		gladiator.health -= (tempArmor > tempDamage? 1 : tempDamage - tempArmor);
		std::cout << name << " attacks " << gladiator.name << " with " << weapon.name << " with " << (tempArmor > tempDamage ? 1 : tempDamage - tempArmor) << " damage" << std::endl;
		armor.dealDamage(tempDamage);
		if (gladiator.health <= 0) {
			std::cout << name << " has killed " << gladiator.name << " with " << weapon.name << std::endl;
			gladiator.dead();
			win();
		}
	}

	operator bool()  {
		return health > 0;
	}

	friend std::ostream& operator<<(std::ostream& out, const IGladiator& gladiator) {
		out << '"' << gladiator.name << '"' << " now has " << gladiator.health << " health" << std::endl;
		return out;
	}

	virtual ~IGladiator() {
		if(&weapon) delete &weapon;
		if(&armor) delete &armor;
	}

};