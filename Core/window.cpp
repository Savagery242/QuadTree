#include "window.h"
#include <iostream>
#include <cmath>
#include <algorithm>

#define PI 3.1415926535
#define DEG2RAD 0.0174533

Window::Window(int width, int height)
{
	this->width = width;
	this->height = height;
	linesIndex = 0;
}

Window::~Window() {}

bool Window::Create()
{
	if (!glfwInit())
	{
		std::cout << "GLFW Init Failed" << std::endl;
		return false;
	}

	window = glfwCreateWindow(width, height, "C++ QuadTree Test", NULL, NULL);

	if (!window)
	{		
		std::cout << "Window Is NULL!" << std::endl;
		return false;
	}

	glfwMakeContextCurrent(window);
	return true;
}

// Don't mind me, just playing with immediate mode... 
// quick and dirty is the name of the game :)

bool Window::Update()
{
	bool windowGood = true;

	if (glfwWindowShouldClose(window))
		windowGood = false;

	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.1, 0.3, 0.5, 1);
	
	// Draw Lines
	for (int line = 0; line < linesIndex; ++line)
	{	
		glBegin(GL_LINES);
		glVertex2d(lines[line].a.x * 2 - 1, lines[line].a.y * 2 - 1);
		glVertex2d(lines[line].b.x * 2 - 1, lines[line].b.y * 2 - 1);
		glEnd();
	}

	linesIndex = 0;

	// Draw Circles
	for (int circle = 0; circle < circlesIndex; ++circle)
	{		
		glBegin(GL_LINE_LOOP);
		int numVertices = std::max((int)(100 * circles[circle].rad), 6);
		for (int v = 0; v < numVertices; ++v)
		{
			double deg = (360 / numVertices) * v;			
			double sin = std::sin(DEG2RAD * deg);
			double cos = std::cos(DEG2RAD * deg);
			double x = (circles[circle].pos.x * 2 - 1) + sin * circles[circle].rad;
			double y = (circles[circle].pos.y * 2 - 1) + cos * circles[circle].rad;
			glVertex2d(x, y);
		}
		glEnd();
	}

	circlesIndex = 0;

	/* Swap front and back buffers */
	glfwSwapBuffers(window);

	/* Poll for and process events */
	glfwPollEvents();

	return windowGood;
}

void Window::Destroy()
{
	glfwTerminate();
}

// LINES

void Window::DrawLine(double x1, double y1, double x2, double y2)
{
	DrawLine(LINE(x1, y1, x2, y2));
}

void Window::DrawLine(POINT a, POINT b)
{
	DrawLine(LINE(a, b));
}

void Window::DrawLine(LINE line)
{
	if (linesIndex >= ARRAY_SIZE)
		linesIndex = 0;

	lines[linesIndex] = line;
	linesIndex++;
}

// CIRCLES

void Window::DrawCircle(POINT pos, double rad)
{
	DrawCircle(CIRCLE(pos, rad));
}

void Window::DrawCircle(CIRCLE circle)
{
	if (circlesIndex >= ARRAY_SIZE)
		circlesIndex = 0;

	circles[circlesIndex] = circle;
	circlesIndex++;
}
