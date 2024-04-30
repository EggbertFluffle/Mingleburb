#pragma once

#include "Block.hpp"
#include "Globals.hpp"
#include "perlin.hpp"

#include <glm/gtc/noise.hpp>
#include <glm/vec2.hpp>
#include <array>

class Chunk {
	std::array<Block, BUILD_HEIGHT * CHUNK_WIDTH * CHUNK_WIDTH> blocks;

public:
	glm::ivec2 chunkCoordinates;

	Chunk(int x, int z);
	Block* getBlock(int x, int y, int z);
	void setBlock(int x, int y, int z, int blockId);
	void setAir(int x, int y, int z);
	void generateNoise(Perlin::perlinOffsets* po);
};
