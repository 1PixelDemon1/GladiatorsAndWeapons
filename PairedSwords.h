#pragma once

#include "IWeapon.h"
#include <random>

class PairedSwords : public IWeapon {
private:

	std::uniform_int_distribution<int> dist;
	std::mt19937 mt;

public:
	PairedSwords(int32_t baseDamage, std::string name, std::mt19937& mt) : IWeapon(baseDamage, name, "sprites/paired_swords.png") {
		dist = std::uniform_int_distribution<int>(0, 2);
		this->mt = mt;
	}
	// Унаследовано через IWeapon
	virtual int32_t damage() {
		return baseDamage * dist(mt);
	}
};