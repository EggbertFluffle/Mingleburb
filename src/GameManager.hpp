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
	uint worldWidth;
	
	GameManager();

	void cullFaces(const int x, const int y, const int z);
	void cullFaces(const glm::vec3& blockCoords);

	void cullSurroundingBlocks(const int x, const int y, const int z);
	void cullSurroundingBlocks(const glm::vec3& blockCoords);

	void cullChunkFaces(Chunk* chunk);

	Block* const getBlock(const int x, const int y, const int z);
	Block* const getBlock(const glm::vec3& blockCoords);

	Block* const getBlockFloored(const float x, const float y, const float z);
	Block* const getBlockFloored(const glm::vec3& blockCoords);

	Chunk* const getChunk(const int x, const int y);

	void setBlock(const int x, const int y, const int z, const int id);
	void setBlock(const glm::vec3& blockCoords, const int id);
};
