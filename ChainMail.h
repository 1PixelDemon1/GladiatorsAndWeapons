#pragma once
#include "IArmor.h"
#include <random>
#include <iostream>

class ChainMail : public IArmor {
private:
	std::uniform_int_distribution<int> dist;
	std::mt19937 mt;
public:
	ChainMail(int32_t defense, int32_t durability, std::string name, std::mt19937& mt) : IArmor{ defense, durability, name, "sprites/chain_mail.png" } {
		dist = std::uniform_int_distribution<int>(0, 5);
		this->mt = mt;
	}

	virtual int32_t value() {
		if (dist(mt) == 0) return 0;
		return defense;
	};

	virtual void dealDamage(int32_t damage) {
		durability -= damage;
		if (durability < 0 && !isBroken) {
			std::cout << name << " has broken!" << std::endl;
			isBroken = true;
			defense = defense / 5;
		}
	};
};