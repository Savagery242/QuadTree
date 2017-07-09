#pragma once

struct POINT
{
	double x;
	double y;
	POINT() {}
	POINT(double x, double y) : x(x), y(y) { }
};

struct LINE
{
	POINT a;
	POINT b;
	LINE(POINT a, POINT b) : a(a), b(b) {}
};

struct RECT
{
	double x;
	double y;
	double width;
	double height;
	RECT() {}
	RECT(double x, double y, double width, double height) :
		x(x), y(y), width(width), height(height)
	{ }
};