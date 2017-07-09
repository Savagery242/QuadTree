#include "window.h"
#include <iostream>

Window::Window(int width, int height)
{
	this->width = width;
	this->height = height;
	vertIndex = 0;
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

bool Window::Update()
{
	bool windowGood = true;

	if (glfwWindowShouldClose(window))
		windowGood = false;

	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.1, 0.3, 0.5, 1);
	
	for (int vert = 0; vert < vertIndex - 1; vert += 2)
	{	
		glBegin(GL_LINES);
		glVertex2d(vertices[vert].x, vertices[vert].y);
		glVertex2d(vertices[vert + 1].x, vertices[vert + 1].y);
		glEnd();
	}

	vertIndex = 0;

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

void Window::DrawLine(POINT &a, POINT &b)
{
	DrawLine(a.x, a.y, b.x, b.y);
}

void Window::DrawLine(LINE &line)
{
	DrawLine(line.a, line.b);
}

void Window::DrawLine(double x1, double y1, double x2, double y2)
{
	vertices[vertIndex] = POINT(x1, y1);
	vertices[vertIndex + 1] = POINT(x2, y2);
	vertIndex += 2;
}
