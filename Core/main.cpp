#include <iostream>
#include "GLFW\glfw3.h"
#include "window.h"
#include "struct.h"
#include "quadtree.h"
#include "entity.h"
#include <vector>
#include <cstdlib>

#define NUM_ENTITIES 80

POINT GetRandomPoint(RECT bounds);
double GetRandomDouble(double min, double max);
double GetRandomDouble();

int main(void)
{
	bool gameOn = true;

	std::vector<LINE> lines;
	std::srand(1084);

	Window window (640, 640);
	Quadtree quadTree(0, RECT(0, 0, 1, 1));
	Entity entities[NUM_ENTITIES];

	// Initialization
	if (!window.Create())
	{
		window.Destroy();
		return -1;
	}

	RECT bounds(0, 0, 1, 1);

	for (int i = 0; i < NUM_ENTITIES; ++i)
	{
		entities[i] = Entity(GetRandomPoint(bounds));
		quadTree.Insert(entities[i]);
	}

	quadTree.GetLines(lines);

	// Game Loop
	while (gameOn)
	{
		// Draw Quad Tree Grid
		typedef std::vector<LINE>::iterator iter;
		for (iter i = lines.begin(); i != lines.end(); ++i)		
			window.DrawLine(*i);		

		// Draw Entity Markers
		for (int i = 0; i < NUM_ENTITIES; ++i)		
			window.DrawCircle(entities[i].location, 0.01);		

		gameOn = window.Update();
	}

	quadTree.Clear();
	return 0;
}

POINT GetRandomPoint(RECT bounds)
{
	double x = GetRandomDouble(bounds.x, bounds.x + bounds.width);
	double y = GetRandomDouble(bounds.y, bounds.y + bounds.height);
	return POINT(x, y);
}

double GetRandomDouble(double min, double max)
{
	return min + GetRandomDouble() * (max - min);
}

double GetRandomDouble()
{
	return (double)std::rand() / RAND_MAX;
}