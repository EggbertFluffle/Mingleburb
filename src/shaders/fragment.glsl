#version 430 core

in vec2 fTex;

out vec4 FragColor;

uniform sampler2D dirtTexture;

void main() {
	// FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	FragColor = texture(dirtTexture, fTex);
}