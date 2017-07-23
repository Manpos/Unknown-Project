#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texCoords;

out vec3 tColor;
out vec2 TexCoords;

uniform mat4 transform;

void main() {
	TexCoords = texCoords;
	tColor = color;
	gl_Position = transform * vec4(position, 0, 1.0);

}