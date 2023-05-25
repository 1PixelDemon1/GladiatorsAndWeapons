#pragma once
#include "IGladiator.h"

class RegularGladiator : public IGladiator
{
public:
	RegularGladiator(IWeapon* weapon, IArmor* armor, int32_t health, std::string name = "Regular") : IGladiator(weapon, armor, health, name, "") {}

	virtual void dead() {
		std::cout << "OH NOOOOOOOO!! "<< name << " will come back! ARGH...\a" << std::endl;
	}

	virtual void win() {
		std::cout << "HAHAHAHA! No gorillas or halflings! We always win! Remember my name : " << name << "!\a" << std::endl;
	}

};

