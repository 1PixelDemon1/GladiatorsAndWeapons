#pragma once

#include <cstdint>
#include <string>

class IGladiator;

class IArmor {
	friend class IGladiator;
protected:
	int32_t defense;
	int32_t durability;
	std::string name;

public:

	IArmor(int32_t defense = 20, int32_t durability = 100, std::string name = "Armor") : 
		defense{ defense }, durability{durability}, name { name } {}

	virtual int32_t value() = 0;
	virtual void dealDamage(int32_t damage) = 0;
};