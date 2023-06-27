#pragma once

#include "IWeapon.h"

class Spear : public IWeapon {

	public: 
		Spear(int32_t baseDamage, std::string name) : IWeapon(baseDamage, name, "sprites/spear.png") {}
		// Унаследовано через IWeapon
		virtual int32_t damage() {
			return baseDamage;
		}
};