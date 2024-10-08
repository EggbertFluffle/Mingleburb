#pragma once

#include "Block.hpp"
#include "Config.hpp"
#include "perlin.hpp"

#include <glm/gtc/noise.hpp>
#include <glm/vec2.hpp>
#include <array>

class Chunk {
	std::array<Block, BUILD_HEIGHT * CHUNK_WIDTH * CHUNK_WIDTH> blocks;

public:
	const glm::ivec2 coords;
	bool loaded;

	Chunk(const int x, const int z);
	Block* const getBlock(const int x, const int y, const int z);
	void setBlock(const int x, const int y, const int z, const int blockId);
	void setAir(const int x, const int y, const int z);
	void generateNoise(Perlin::perlinOffsets* po);
};
