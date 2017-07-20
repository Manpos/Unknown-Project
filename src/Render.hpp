#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW\glfw3.h>
#include <thread>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <glm.hpp>
#include "shader.hpp"

#include <SOIL.h>

using namespace glm;
using namespace std;

#define R Render::Instance()

class Render {
private:
	GLFWwindow* window;

#pragma region Tutorial

	Shader *test;
	GLfloat *vertices;
	GLuint *elements;
	GLuint vao;
	GLuint vbo;
	GLuint ebo;

	vector<GLuint> textureBuffer;

	// SOIL Texture Load buffer
	unsigned char* image;

	// Uniform variables
	GLint uniColor;

#pragma endregion	

public:

	static Render& Instance();
	void Start(int, int);
	void Update();
	void LoadTexture(GLchar* path);
	~Render();

};