#version 330 core

uniform vec3 triangleColor;

in vec3 tColor;
in vec2 TexCoords;

out vec4 color;

// Texture uniform
uniform sampler2D tex0;
uniform sampler2D tex1;

void main() {

	color = mix(texture(tex0, TexCoords), texture(tex1, TexCoords), 0.5);

}	