#version 430 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTex;

out vec2 fTex;

uniform mat4 model;
uniform vec2 resolution;

void main() {
	gl_Position = model * vec4(aPos.x * (resolution.y / resolution.x), aPos.y, 0.0f, 1.0f);
	// gl_Position = model * vec4(aPos.xy / resolution.xy, 0.0f, 1.0f);
	fTex = aTex;
}
