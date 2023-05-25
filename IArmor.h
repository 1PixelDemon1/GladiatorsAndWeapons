#pragma once

#include "PNGstConsoleIMage.h"
#include <cstdint>
#include <string>

class IGladiator;

class IArmor {
	friend class IGladiator;
protected:
	int32_t defense;
	int32_t durability;
	std::string name;
	bool isBroken;
	PNGstConsoleIMage image;

public:

	IArmor(int32_t defense, int32_t durability, std::string name, std::string filename) :
		defense{ defense }, durability{ durability }, name{ name }, image{ filename }, isBroken{ false } {}

	virtual void setPosition(int32_t x, int32_t y) {
		image.setPosition(x, y);
	}

	virtual void draw() {
		image.draw();
	}
	void flip() {
		image.flipped = !image.flipped;
	}

	virtual int32_t value() = 0;
	virtual void dealDamage(int32_t damage) = 0;
};