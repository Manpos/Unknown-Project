#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW\glfw3.h>
#include <thread>

class Render {
private:
	GLFWwindow* window;
public:
	void Start(int, int);
	void Update();
};