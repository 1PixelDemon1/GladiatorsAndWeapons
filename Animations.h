#pragma once
#include <cstdint>
#include <windows.h>

class HealthBar {
public:

	static HWND hwnd;
	static HDC dc;
	int32_t x;
	int32_t y;
	
	double maxValue;
	double curValue;

	HealthBar(int32_t x, int32_t y, double maxValue, double curValue = 0) : x{ x }, y{ y }, maxValue{maxValue}, curValue{curValue} {}

	void operator()(int32_t newValue) {
		
		curValue = newValue;
		HBRUSH brush{ CreateSolidBrush(RGB(220, 0, 0)) };
		
		SelectObject(dc, brush);
		Rectangle(dc, x, y, x + maxValue, y + maxValue / 8);
		DeleteObject(brush);
		brush = CreateSolidBrush(RGB((maxValue - curValue) / maxValue * 255, 255 - (maxValue - curValue) / maxValue * 255, 0));
		SelectObject(dc, brush);
		Rectangle(dc, x, y, x + curValue, y + maxValue / 8);
		DeleteObject(brush);
	}
	void operator()() {
		operator()(curValue);
	}

	void setPosition(int32_t x, int32_t y) {
		this->x = x;
		this->y = y;
	}

};
HWND HealthBar::hwnd{GetConsoleWindow()};
HDC HealthBar::dc{GetDC(hwnd)};

class Slash {
private:
	int32_t x;
	int32_t y;
	uint8_t state;
	PNGstConsoleIMage arr[3];

public:
	Slash(int32_t x, int32_t y) : 
		x{ x }, y{ y }, state{ 0 }, arr{ {"sprites/slash_1.png"}, {"sprites/slash_2.png"}, {"sprites/slash_3.png"} } {
		arr[0].setPosition(x, y);
		arr[1].setPosition(x, y);
		arr[2].setPosition(x, y);
	}

	void flip() {
		arr[0].flipped = !arr[0].flipped;
		arr[1].flipped = !arr[1].flipped;
		arr[2].flipped = !arr[2].flipped;
	}

	void operator()() {
		arr[state].draw();
		state = (state + 1) % 3;
	}

	void setPosition(int32_t x, int32_t y) {
		arr[0].setPosition(x, y);
		arr[1].setPosition(x, y);
		arr[2].setPosition(x, y);
	}

};

class Damage {
private:
	static HWND hwnd;
	static HDC dc;
	int32_t x;
	int32_t y;
public:
	Damage(int32_t x, int32_t y) : x{ x + 128 }, y{ y - 60 }{}

	void operator()(int32_t damage) {
		char buffer[50];
		_itoa(damage, buffer, 10);
		
		HFONT hFont1 = CreateFont(damage > 10? 80 : 60, 0, 0, 0, FW_ULTRABOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Comic Sans MS"));

		SelectObject(dc, hFont1);
		SetTextColor(dc, (damage == 0) ? RGB(0, 255, 0) : (damage < 10) ? RGB(255, 180, 0) : RGB(255, 0, 0));
		SetBkColor(dc, GetPixel(dc, 0, 0));
		TextOutA(dc, x, y, buffer, strlen(buffer) + 1);
		
		DeleteObject(hFont1);		
	}

	void setPosition(int32_t x, int32_t y) {
		this->x = x + 100;
		this->y = y - 48;
	}
};
HWND Damage::hwnd{GetConsoleWindow()};
HDC Damage::dc{GetDC(hwnd)};