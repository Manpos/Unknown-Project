#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW\glfw3.h>
#include <thread>
#include <stdio.h>
#include <glm.hpp>
#include "shader.hpp"

using namespace glm;

#define R Render::Instance()

class Render {
private:
	GLFWwindow* window;

#pragma region EraseRegion

	Shader *test;
	GLfloat *vertices;
	GLuint vao;
	GLuint vbo;

#pragma endregion	

public:

	static Render& Instance();
	void Start(int, int);
	void Update();
	~Render();

};