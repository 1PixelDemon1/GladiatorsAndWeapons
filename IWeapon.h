#pragma once
#include "PNGstConsoleIMage.h"
#include <cstdint>
#include <string>

class IGladiator;

class IWeapon {

	friend class IGladiator;

protected:
	int32_t baseDamage;
	std::string name;
	PNGstConsoleIMage image;

public:

	IWeapon(int32_t baseDamage, std::string name, std::string filename) : baseDamage{ baseDamage }, name{ name }, image{filename} {}


	virtual std::string getName() { return name; }

	virtual int32_t damage() = 0;

	virtual void setPosition(int32_t x, int32_t y) {
		image.setPosition(x, y);
	}

	virtual void draw() {
		image.draw();		
	}

	void flip() {
		image.flipped = !image.flipped;
	}
};