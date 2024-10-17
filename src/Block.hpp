#pragma once

#include <array>
#include <glm/glm.hpp>

inline const std::array<std::array<float, 20>, 6> RECT_VERTICES = {
	// right 1000 0000
	std::array<float, 20>({
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, -1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, -1.0f, 1.0f, 1.0f
	}),
	// left 0100 0000
	std::array<float, 20>({
		-1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-1.0f, 1.0f, -1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, -1.0f, 1.0f, 1.0f
	}),
	// top 0010 0000
	std::array<float, 20>({
		-1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, -1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, -1.0f, 1.0f, 1.0f
	}),
	// bottom 0001 0000
	std::array<float, 20>({
		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, -1.0f, 1.0f, 1.0f
	}),
	// back 0000 1000
	std::array<float, 20>({
		-1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 1.0f, 1.0f, 1.0f
	}),
	// front 0000 0100
	std::array<float, 20>({
		-1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, -1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, -1.0f, 1.0f, 1.0f
	})
};

namespace BLOCK_NORMAL {
	inline const glm::vec3 POSITIVE_X(1, 0, 0);
	inline const glm::vec3 NEGATIVE_X(-1, 0, 0);
	inline const glm::vec3 POSITIVE_Y(0, 1, 0);
	inline const glm::vec3 NEGATIVE_Y(0, -1, 0);
	inline const glm::vec3 POSITIVE_Z(0, 0, 1);
	inline const glm::vec3 NEGATIVE_Z(0, 0, -1);
}

struct Block {
	int id;
	unsigned char faces;
	bool highlighted;

	Block() : id(0), faces(0), highlighted(false) {}
	Block(const int i) : id(i), highlighted(false) {}
};
