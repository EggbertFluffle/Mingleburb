#pragma once

#include <array>

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

inline const std::array<float, 20> RECT_LEFT = {
	-1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-1.0f, 1.0f, -1.0f, 1.0f, 0.0f,
	-1.0f, -1.0f, 1.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 1.0f, 1.0f
};

inline const std::array<float, 20> RECT_RIGHT = {
	1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	1.0f, 1.0f, -1.0f, 1.0f, 0.0f,
	1.0f, -1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 1.0f, 1.0f
};

inline const float RECT_TOP[] = {
	-1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-1.0f, 1.0f, -1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, -1.0f, 1.0f, 1.0f
};

inline const std::array<float, 20> RECT_BOTTOM = {
	-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
	1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
	-1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 1.0f, 1.0f
};

inline const std::array<float, 20> RECT_FRONT = {
	-1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
	1.0f, 1.0f, -1.0f, 1.0f, 0.0f,
	-1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 1.0f, 1.0f
};

inline const std::array<float, 20> RECT_BACK = {
	-1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-1.0f, -1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, -1.0f, 1.0f, 1.0f, 1.0f
};

inline const std::array<int, 6> RECT_INDICES = {
	0, 1, 2,
	1, 2, 3
};

struct Block {
	int id;
	unsigned char faces;
	bool highlighted;

	Block() : id(0), faces(0), highlighted(false) {}
	Block(const int i) : id(i), highlighted(false) {}
};
