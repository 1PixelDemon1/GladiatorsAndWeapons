#pragma once
#include "IArmor.h"
#include <random>
#include <iostream>

class LeatherArmor : public IArmor{
private:

public:
	LeatherArmor(int32_t defense, int32_t durability, std::string name) : IArmor{ defense, durability, name, "sprites/leather_armor.png" } {}
	
	virtual int32_t value() {
		return defense;
	};
	
	virtual void dealDamage(int32_t damage) {
		durability -= damage;
		if (durability < 0 && defense != 0) {
			std::cout << name << " has broken!" << std::endl;
			isBroken = true;
			defense = 0;
		}
	};
};