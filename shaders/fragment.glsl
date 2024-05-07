#version 430 core

in vec2 fTex;

out vec4 FragColor;

uniform sampler2D loadedTexture;
uniform bool highlighted;
uniform bool debug;

uniform float luminence;

void main() {
	FragColor = texture(loadedTexture, fTex);
	FragColor = mix(FragColor, vec4(0.0f, 0.0f, 0.0f, 1.0f), luminence);
	if(highlighted) {
		FragColor = mix(FragColor, vec4(1.0f, 1.0f, 1.0f, 1.0f), 0.5f);
	}
	// if(debug) {
	// 	FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	// }
}
