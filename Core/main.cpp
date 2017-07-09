#include <iostream>
#include "GLFW\glfw3.h"
#include "window.h"
#include "struct.h"
#include "quadtree.h"
#include "entity.h"
#include <vector>

bool gameOn;

int main(void)
{
	std::vector<LINE> lines;

	Window window (640, 480);
	Quadtree quadTree(0, RECT(0, 0, 1, 1));

	gameOn = true;

	// Initialization
	if (!window.Create())
	{
		window.Destroy();
		return -1;
	}

	Entity e1(POINT(0.1, 0.4));
	Entity e2(POINT(0.5, 0.9));
	Entity e3(POINT(0.9, 0.1));
	Entity e4(POINT(0.1, 0.9));
	Entity e5(POINT(0.3, 0.6));
	Entity e6(POINT(0.3, 0.54));
	Entity e7(POINT(0.3, 0.53));
	Entity e8(POINT(0.3, 0.52));
	Entity e9(POINT(0.3, 0.51));

	quadTree.Insert(e1);
	quadTree.Insert(e2);
	quadTree.Insert(e3);
	quadTree.Insert(e4);
	quadTree.Insert(e5);
	quadTree.Insert(e6);
	quadTree.Insert(e7);
	quadTree.Insert(e8);
	quadTree.Insert(e9);

	quadTree.GetLines(lines);

	// Game Loop
	while (gameOn)
	{
		//POINT a(-0.5,  0.5);
		//POINT b(-0.5, -0.5);
		//window.DrawLine(a, b);
		//window.DrawLine(0,0,0.5,0.5);

		typedef std::vector<LINE>::iterator iter;
		for (iter i = lines.begin(); i != lines.end(); ++i)
		{
			window.DrawLine(*i);
		}

		gameOn = window.Update();
	}

	quadTree.Clear();

	return 0;
}