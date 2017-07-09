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
	LINE() {}
	LINE(POINT a, POINT b) : a(a), b(b) {}
	LINE(double x1, double y1, double x2, double y2)
	{
		a = POINT(x1, y1);
		b = POINT(x2, y2);
	}
};

struct CIRCLE
{
	POINT pos;
	double rad;
	CIRCLE() {}
	CIRCLE(POINT pos, double rad) : pos(pos), rad(rad) {}
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