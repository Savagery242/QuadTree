#pragma once

#include "GLFW\glfw3.h"
#include "struct.h"

#define ARRAY_SIZE 4096

class Window
{
private:

	int width;
	int height;
	GLFWwindow *window;

	LINE lines[ARRAY_SIZE];
	int linesIndex;

	RECT quads[ARRAY_SIZE];
	int quadsIndex;

	CIRCLE circles[ARRAY_SIZE];
	int circlesIndex;

public:

	Window(int width, int height);
	~Window();

	bool Create();

	void DrawLine(double x1, double y1, double x2, double y2);
	void DrawLine(POINT a, POINT b);
	void DrawLine(LINE line);

	//void DrawQuad(RECT rect);
	//void DrawQuad(POINT p1, POINT p2, POINT p3, POINT p4);

	void DrawCircle(CIRCLE circle);
	void DrawCircle(POINT pos, double rad);

	bool Update();
	void Destroy();
};