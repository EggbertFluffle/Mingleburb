#version 430 core

in vec2 fTex;

out vec4 FragColor;

uniform sampler2D loadedTexture;

void main() {
	vec4 texColor = texture(loadedTexture, fTex);
	if(texColor.a <= 0.1f) {
		discard;
	}
	FragColor = texColor;
}
