#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW\glfw3.h>
#include <SOIL.h>

#include <thread>
#include <stdio.h>
#include <vector>

#include "shader.hpp"
#include "Transform.h"

#include <iostream>

using namespace std;

#define R Render::Instance()

class Render {
private:
	GLFWwindow* window;
	mat4 defaultMatrix;

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

	mat4 transformMat;
	static Render& Instance();
	void Start(int, int);
	void Draw();
	void LoadTexture(GLchar* path);

	~Render();

};