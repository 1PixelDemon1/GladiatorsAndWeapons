#pragma once

#include <cstdint>
#include <string>

class IGladiator;

class IWeapon {

	friend class IGladiator;

protected:
	int32_t baseDamage;
	std::string name;
public:

	IWeapon(int32_t baseDamage = 10, std::string name = "Weapon") : baseDamage{baseDamage}, name{name} {}

	virtual std::string getName() { return name; }

	virtual int32_t damage() = 0;

};