#pragma once

#include "IWeapon.h"
#include "IArmor.h"
#include "PNGstConsoleIMage.h"
#include "Animations.h"
#include <cstdint>
#include <thread>
#include <iostream>


class IGladiator {
protected:
	int32_t health;
	std::string name;
	IWeapon& weapon;
	IArmor& armor;
	PNGstConsoleIMage image;
	HealthBar healthBar;
	Slash slash;
	Damage damage;
	Dead deadImage;

	int32_t getDamage() {
		return weapon.baseDamage;
	}
	int32_t getDefense() {
		return armor.defense;
	}

	void setDamage(int32_t damage) {
		weapon.baseDamage = damage;
	}

	void setDefense(int32_t defense) {
		armor.defense = defense;
	}

public:

	IGladiator(IWeapon* weapon, IArmor* armor, int32_t health, std::string name, std::string filename) : 
		weapon{ *weapon }, armor{ *armor }, health{ health }, 
		name{ name }, image{filename},
		healthBar{ 0, 0, health, health }, 
		slash{ 0, 0 }, damage{ 0, 0 }, deadImage{0, 0} {

		slash.flip();
	}

	virtual void dead() = 0;

	virtual void win() = 0;

	virtual void setPosition(int32_t x, int32_t y) {
		image.setPosition(x, y);
		healthBar.setPosition(x, y + image.getHeight() + 5);
		armor.setPosition(x, y);
		weapon.setPosition(x, y);
		deadImage.setPosition(x, y);
	}

	virtual void draw() {
		image.draw();
		if(!armor.isBroken) armor.draw();
		weapon.draw();
		healthBar(health);
	}

	
	virtual int32_t getHealth()  { return health; }

	virtual void dealDamage(IGladiator& gladiator) {
		int32_t tempDamage{ weapon.damage() };
		int32_t tempArmor{ gladiator.armor.value()};
		gladiator.health -= (tempArmor > tempDamage? 1 : tempDamage - tempArmor);
		std::cout << name << " attacks " << gladiator.name << " with " << weapon.name << " with " << (tempArmor > tempDamage ? 1 : tempDamage - tempArmor) << " damage" << std::endl;
		gladiator.armor.dealDamage(tempDamage);
		
		slash.setPosition(gladiator.image.getPosition().X, gladiator.image.getPosition().Y);
		damage.setPosition(gladiator.image.getPosition().X, gladiator.image.getPosition().Y);
		damage((tempArmor > tempDamage ? 1 : tempDamage - tempArmor));
		slash();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		slash();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		slash();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));


		if (gladiator.health <= 0) {
			std::cout << name << " has killed " << gladiator.name << " with " << weapon.name << std::endl;
			gladiator.dead();
			win();
		}
	}

	void flip() {
		image.flipped = !image.flipped;
		weapon.flip();
		armor.flip();
		slash.flip();
	}

	operator bool()  {
		return health > 0;
	}

	friend std::ostream& operator<<(std::ostream& out, const IGladiator& gladiator) {
		//out << '"' << gladiator.name << '"' << " now has " << gladiator.health << " health" << std::endl;
		return out;
	}

	virtual ~IGladiator() {
		if(&weapon) delete &weapon;
		if(&armor) delete &armor;
	}

};