#include "Chunk.hpp"
#include "Block.hpp"
#include "Config.hpp"

Chunk::Chunk(const int x, const int z) :
	coords(x, z),
	loaded(false)
{}

void Chunk::generateNoise(Perlin::perlinOffsets* po){
	for(int z = 0; z < CHUNK_WIDTH; z++) {
		for(int y = 0; y < BUILD_HEIGHT; y++) {
			for(int x = 0; x < CHUNK_WIDTH; x++) {
				const int height = BUILD_HEIGHT * ((getPerlinNoise(po, ((x + coords.x * CHUNK_WIDTH) / float(CHUNK_WIDTH)) * NOISE_FREQUENCY, ((z + coords.y * CHUNK_WIDTH) / float(CHUNK_WIDTH)) * NOISE_FREQUENCY) / 2) + 0.5f);
				if (y < height) {
					setBlock(x, y, z, 2);
				} else {
					setAir(x, y, z);
				}
			}
		}
	}
}

Block* const Chunk::getBlock(const int x, const int y, const int z) {
	return &blocks.at((CHUNK_WIDTH * CHUNK_WIDTH * z) + (y * CHUNK_WIDTH) + x);
}

void Chunk::setBlock(const int x, const int y, const int z, const int blockId) {
	blocks.at((CHUNK_WIDTH * CHUNK_WIDTH * z) + (y * CHUNK_WIDTH) + x).id = blockId;
}

void Chunk::setAir(const int x, const int y, const int z) {
	blocks.at((CHUNK_WIDTH * CHUNK_WIDTH * z) + (y * CHUNK_WIDTH) + x).id = 0;
}
