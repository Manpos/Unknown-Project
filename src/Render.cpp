#include "Render.hpp"

Render& Render::Instance()
{
	static Render inst;
	return inst;
};


void Render::Start(int wWidth, int wHeight) {
	// OpenGL initialization
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(wWidth, wHeight, "Unknown", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

#pragma region Tutorial

	vertices = new GLfloat[28]{
		-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
		0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
	};

	elements = new GLuint[6]{
		0, 1, 2,
		2, 3, 0
	};

	// Create Vertex Array Object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	// Create ebo
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 6, elements, GL_STATIC_DRAW);

	// Create Vertex buffer object
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 28, vertices, GL_STATIC_DRAW);

	test = new Shader("./src/VertexShader.vs", "./src/FragmentShader.fs");
	test->USE();

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2*sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5*sizeof(float)));
	glEnableVertexAttribArray(2);
	
	// Uniform things
	uniColor = glGetUniformLocation(test->Program, "triangleColor");

	glUniform3f(uniColor, 1.0f, 1.0f, 0.0f);

	// Alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Store width and height
	glfwGetFramebufferSize(window, &width, &height);

	// Transform matrix
	transformMat = defaultMatrix;

	glViewport(0, 0, width, height);

	//projection = perspective(radians(45.f), 800.f / 800.f, 0.1f, 100.0f);
	//projection = perspective(radians(45.f), float(width) / float(height), 0.1f, 100.0f);
	projection = ortho(-1.0f, 1.f, -1.0f, 1.0f, 0.1f, 100.0f);

#pragma endregion
	
}

void Render::Draw() {

	// While loop, it will be in use meanwhile the application is open
	while (!glfwWindowShouldClose(window)) {

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		
		model = defaultMatrix;
		view = defaultMatrix;

		T.RotateObject(model, glfwGetTime() * 150.f, T.x);
		T.TranslateObject(view, -3.f, T.z);

		//T.TranslateObject(model, vec3(0.0f), vec3(0.0f, 0.0f, 0.0f));
		//T.RotateObject(model, glfwGetTime() * 150.f, T.y);
		//T.ScaleObject(model, T.x, 1.0f);

		test->USE();

		unsigned int modelLoc = glGetUniformLocation(test->Program, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
		unsigned int viewLoc = glGetUniformLocation(test->Program, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
		unsigned int projectionLoc = glGetUniformLocation(test->Program, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(projection));

		// Clear the screen to black
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw a triangle from the 3 vertices
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

}

void Render::LoadTexture(GLchar* path) {

	// SOIL load parameters
	int width, height;
	textureBuffer.push_back(0);

	string textureName = "tex" + std::to_string(textureBuffer.size() - 1);
	
	glActiveTexture(GL_TEXTURE0 + textureBuffer.size() - 1);

	glGenTextures(1, &textureBuffer.back());
	glBindTexture(GL_TEXTURE_2D, textureBuffer.back());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// SOIL Texture loading
	image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);

	glUniform1i(glGetUniformLocation(test->Program, textureName.c_str()), textureBuffer.size() - 1);

}

Render::~Render() {
	delete test;
	delete vertices;
}
