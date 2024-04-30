#pragma once

#include <glm/glm.hpp>
#include <forward_list>

#include "Block.hpp"
#include "Chunk.hpp"
#include "perlin.hpp"

class GameManager {
	Perlin::perlinOffsets* po;
	
public:
	std::forward_list<Chunk> chunks;
	float faceLuminence[6];
	unsigned int worldWidth;
	
	GameManager();
	void cullFaces(int x, int y, int z);
	void cullSurroundingBlocks(glm::vec3& selectedBlockCoords);
	void cullChunkFaces(Chunk* chunk);
	Block* getBlock(int x, int y, int z);
	Chunk* getChunk(int x, int y);

	glm::vec3 directionalLight;
};
