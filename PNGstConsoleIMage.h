#pragma once

typedef unsigned char ubyte_;

#include <windows.h>
#include <string>
#include <vector>
#include "lodepng/lodepng.h"

class PNGstConsoleIMage
{
private:
	std::vector<ubyte_> map;

	struct {
		unsigned width;
		unsigned height;
	} size;

	COORD position;

	HDC hdc;

	void getPNGImageInfo(std::string file);

public:

	unsigned getWidth() {
		return size.width;
	}

	unsigned getHeight() {
		return size.height;
	}

	bool flipped;

	PNGstConsoleIMage(std::string filename, bool flipped = false) : hdc{ GetDC(GetConsoleWindow()) }, position{}, flipped{flipped}
	{
		getPNGImageInfo(filename);
	}

	void setPosition(int16_t x, int16_t y);

	COORD getPosition();

	void draw();

	virtual ~PNGstConsoleIMage() {
	}
};

