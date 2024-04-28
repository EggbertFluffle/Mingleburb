#pragma once

#include <unordered_map>
#include <string> 

const float RECT_VERTICES[6][20] = {
	// right 1000 0000
	{
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, -1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, -1.0f, 1.0f, 1.0f
	},
	// left 0100 0000
	{
		-1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-1.0f, 1.0f, -1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, -1.0f, 1.0f, 1.0f
	},
	// top 0010 0000
	{
		-1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, -1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, -1.0f, 1.0f, 1.0f
	},
	// bottom 0001 0000
	{
		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, -1.0f, 1.0f, 1.0f
	},
	// back 0000 1000
	{
		-1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 1.0f, 1.0f, 1.0f
	},
	// front 0000 0100
	{
		-1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, -1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, -1.0f, 1.0f, 1.0f
	}
};

const float RECT_LEFT[] = {
	-1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-1.0f, 1.0f, -1.0f, 1.0f, 0.0f,
	-1.0f, -1.0f, 1.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 1.0f, 1.0f
};
const float RECT_RIGHT[] = {
	1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	1.0f, 1.0f, -1.0f, 1.0f, 0.0f,
	1.0f, -1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 1.0f, 1.0f
};

const float RECT_TOP[] = {
	-1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-1.0f, 1.0f, -1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, -1.0f, 1.0f, 1.0f
};

const float RECT_BOTTOM[] = {
	-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
	1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
	-1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 1.0f, 1.0f
};

const float RECT_FRONT[] = {
	-1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
	1.0f, 1.0f, -1.0f, 1.0f, 0.0f,
	-1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 1.0f, 1.0f
};

const float RECT_BACK[] = {
	-1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-1.0f, -1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, -1.0f, 1.0f, 1.0f, 1.0f
};

const int RECT_INDICES[] = {
	0, 1, 2,
	1, 2, 3
};

const std::unordered_map<std::string, unsigned int> BLOCK_TEXTURE_ID_TABLE;

struct Block {
	int id;
	unsigned char faces;
	bool highlighted;

	Block() : id(BLOCK_TEXTURE_ID_TABLE.at("dirt")) {}
	Block(const char* textureName) {
		BLOCK_TEXTURE_ID_TABLE.at(textureName);
	};
};
