#pragma once

#include <glm/glm.hpp>
#include <forward_list>

#include "Block.hpp"
#include "perlin.hpp"
#include "Chunk.hpp"

class GameManager {
	Perlin::perlinOffsets* po;
	
public:
	std::forward_list<Chunk> chunks;
	glm::vec3 directionalLight;
	float faceLuminence[6];
	unsigned int worldWidth;
	
	GameManager();
	void cullFaces(const int x, const int y, const int z);
	void cullSurroundingBlocks(glm::vec3& selectedBlockCoords);
	void cullChunkFaces(Chunk* chunk);
	Block* const getBlock(const int x, const int y, const int z);
	Chunk* const getChunk(const int x, const int y);
};
