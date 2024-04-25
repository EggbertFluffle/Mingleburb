#pragma once

#include <glm/glm.hpp>

#include "Block.hpp"
#include "Globals.hpp"

class GameManager {
public:
	Block blocks[CHUNK_WIDTH][BUILD_HEIGHT][CHUNK_WIDTH];
	float faceLuminence[6];

	GameManager();
	void cullFaces(int x, int y, int z);
	void cullSurroundingBlocks(glm::vec3& selectedBlockCoords);
	Block* getBlock(int x, int y, int z);

	glm::vec3 directionalLight;
};
