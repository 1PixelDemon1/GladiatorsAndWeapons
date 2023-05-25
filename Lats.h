#pragma once
#include "IArmor.h"
#include <random>
#include <iostream>

class Lats : public IArmor {
private:
	std::uniform_int_distribution<int> dist;
	std::mt19937 mt;
public:
	Lats(int32_t defense, int32_t durability, std::string name, std::mt19937& mt) : IArmor{ defense, durability, name, "sprites/lats.png" } {
		dist = std::uniform_int_distribution<int>(0, 10);
		this->mt = mt;
	}

	virtual int32_t value() {
		if (isBroken) return defense;
		if (dist(mt) < 3) return 999;
		return defense;
	};

	virtual void dealDamage(int32_t damage) {
		durability -= damage;		
		if ((durability < 0 || dist(mt) == 10) && defense != 0) {
			std::cout << name << " has broken!" << std::endl;
			isBroken = true;
			defense = 0;
		}
	};
};