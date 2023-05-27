#pragma once

#include "IWeapon.h"
#include <random>

class Bow : public IWeapon {
private:

	std::uniform_int_distribution<int> dist;
	std::mt19937 mt;

public:
	Bow(int32_t baseDamage, std::string name, std::mt19937& mt) : IWeapon(baseDamage, name, "sprites/bow.png") {
		dist = std::uniform_int_distribution<int>(0, 15);
		this->mt = mt;
	}
	// Унаследовано через IWeapon
	virtual int32_t damage() {
		int32_t temp{ dist(mt) };
		if (temp == 15)
			return baseDamage * 5;
		else if (temp < 8) {
			return 0;
		}
		else
			return baseDamage;
	}
};