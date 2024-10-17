#pragma once

#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <vector>

#include "Shader.hpp"

struct DebugPoint {
	glm::vec3 pos;
	glm::vec3 color;
	float buffer[6];

	DebugPoint(float x, float y, float z) : pos(x, y, z), color(127, 127, 127) {}
	DebugPoint(float x, float y, float z, float r, float g, float b) : pos(x, y, z), color(r, g, b) {}
	
	float* getBuffer() {
		buffer[0] = pos.x;
		buffer[1] = pos.y;
		buffer[2] = pos.z;
		buffer[3] = color.x;
		buffer[4] = color.y;
		buffer[5] = color.z;
		return buffer;
	}
};

class Debug {
public:
	std::vector<DebugPoint> points;
	// Shader shader;

	Debug() {
		// shader.compileShaders("./shaders/debugVertex.glsl", "./shaders/debugFragment.glsl");
	}

	void clearQueue() {
		points.clear();
	}

	void addDebugPoint(float x, float y, float z) {
		points.push_back(DebugPoint(x, y, z));
	}

	void addDebugPoint(float x, float y, float z, float r, float g, float b) {
		points.push_back(DebugPoint(x, y, z, r, g, b));
	}
};

