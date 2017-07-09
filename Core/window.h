#pragma once

#include "GLFW\glfw3.h"
#include "struct.h"

class Window
{
private:

	int width;
	int height;
	GLFWwindow *window;

	POINT vertices[1000];
	int vertIndex;

public:

	Window(int width, int height);
	~Window();

	bool Create();
	void DrawLine(double x1, double y1, double x2, double y2);
	void DrawLine(POINT &a, POINT &b);
	void DrawLine(LINE &line);
	bool Update();
	void Destroy();
};