#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

using namespace glm;

#define T Transform::Instance()



class Transform {

public:
	enum AXIS { x, y, z };
	static Transform& Instance() {
		static Transform inst;
		return inst;
	};

	void RotateObject(mat4 &inMatrix, float degrees, AXIS axis) {
		vec3 currentAxis;

		switch (axis)
		{
		case x:
			currentAxis = vec3(1.0f, 0.0f, 0.0f);
			break;
		case y:
			currentAxis = vec3(0.0f, 1.0f, 0.0f);
			break;
		case z:
			currentAxis = vec3(0.0f, 0.0f, 1.0f);
			break;
		}
		
		inMatrix = rotate(inMatrix, radians(degrees), currentAxis);
	}

	mat4 RotateObject(float degrees, AXIS axis) {
		vec3 currentAxis;
		mat4 outMatrix;

		switch (axis)
		{
		case x:
			currentAxis = vec3(1.0f, 0.0f, 0.0f);
			break;
		case y:
			currentAxis = vec3(0.0f, 1.0f, 0.0f);
			break;
		case z:
			currentAxis = vec3(0.0f, 0.0f, 1.0f);
			break;
		}

		return rotate(outMatrix, radians(degrees), currentAxis);
	}

	void TranslateObject(mat4 &inMatrix, float displacement, AXIS axis) {
		vec3 currentAxis;

		switch (axis)
		{
		case x:
			currentAxis = vec3(1.0f, 0.0f, 0.0f);
			break;
		case y:
			currentAxis = vec3(0.0f, 1.0f, 0.0f);
			break;
		case z:
			currentAxis = vec3(0.0f, 0.0f, 1.0f);
			break;
		}

		inMatrix = translate(inMatrix, currentAxis * displacement);
	}

	void ScaleObject(mat4 &inMatrix, AXIS axis, float variation = 1.0f) {
		vec3 currentAxis;

		switch (axis)
		{
		case x:
			currentAxis = vec3(1.0f * variation, 1.0f, 1.0f);
			break;
		case y:
			currentAxis = vec3(1.0f, 1.0f * variation, 1.0f);
			break;
		case z:
			currentAxis = vec3(1.0f, 1.0f, 1.0f * variation);
			break;
		}

		inMatrix = scale(inMatrix, currentAxis);
	}

};