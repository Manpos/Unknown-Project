#version 330 core

uniform vec3 triangleColor;

in vec3 tColor;
in vec2 TexCoords;

out vec4 color;

// Texture uniform
uniform sampler2D tex;

void main() {

	color = texture(tex, TexCoords);

}	