#version 430 core

in vec2 fTex;

out vec4 FragColor;

uniform sampler2D dirtTexture;
uniform bool highlighted;

void main() {
	if(highlighted) {
		FragColor = mix(texture(dirtTexture, fTex), vec4(1.0f, 1.0f, 1.0f, 1.0f), 0.5f);
	} else {
		FragColor = texture(dirtTexture, fTex);
	}
}
