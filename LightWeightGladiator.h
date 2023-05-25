#pragma once
#include "IGladiator.h"

class LightWeightGladiator : public IGladiator
{
public:
	LightWeightGladiator(IWeapon* weapon, IArmor* armor, int32_t health, std::string name = "Light Weight") :
		IGladiator(weapon, armor, health, name, "") {
		setDamage(getDamage() * 1.5);
		setDefense(getDefense() / 1.7);
	}

	virtual void dead() {
		std::cout << name << " is blown away! " << std::endl;
	}

	virtual void win() {
		std::cout << "Dont you ever come to " << name << " again!\a" << std::endl;
	}

};

