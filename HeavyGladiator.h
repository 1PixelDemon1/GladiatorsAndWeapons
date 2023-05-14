#pragma once
#include "IGladiator.h"

class HeavyGladiator : public IGladiator
{
public:
	HeavyGladiator(IWeapon* weapon, IArmor* armor, int32_t health, std::string name = "Heavy") : 
		IGladiator(weapon, armor, health, name) {
		setDamage(getDamage() / 1.6);
		setDefense(getDefense() * 1.6);
	}

	virtual void dead() {
		std::cout << name << " smashes the ground with it`s body! " << std::endl;
	}

	virtual void win() {
		std::cout << name << "wins! : "<< "I am " << name << "!\a" << std::endl;
	}

};

