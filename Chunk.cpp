#include "Chunk.hpp"
#include "Globals.hpp"
#include "Block.hpp"

Chunk::Chunk(int x, int z) :
	chunkCoordinates(x, z)
{}


void Chunk::generateNoise(Perlin::perlinOffsets* po){
	for(int z = 0; z < CHUNK_WIDTH; z++) {
		for(int y = 0; y < BUILD_HEIGHT; y++) {
			for(int x = 0; x < CHUNK_WIDTH; x++) {
				int height = BUILD_HEIGHT * ((getPerlinNoise(po, ((x + chunkCoordinates.x * CHUNK_WIDTH) / float(CHUNK_WIDTH)) * NOISE_FREQUENCY, ((z + chunkCoordinates.y * CHUNK_WIDTH) / float(CHUNK_WIDTH)) * NOISE_FREQUENCY) / 2) + 0.5f);

				if (y < height) {
					setBlock(x, y, z, "dirt");
				} else {
					setAir(x, y, z);
				}
			}
		}
	}
}

Block* Chunk::getBlock(int x, int y, int z) {
	return &(blocks[(CHUNK_WIDTH * CHUNK_WIDTH * z) + (y * CHUNK_WIDTH) + x]);
}

void Chunk::setBlock(int x, int y, int z, const char* blockName) {
	blocks[(CHUNK_WIDTH * CHUNK_WIDTH * z) + (y * CHUNK_WIDTH) + x] = Block(blockName);
}

void Chunk::setAir(int x, int y, int z) {
	blocks[(CHUNK_WIDTH * CHUNK_WIDTH * z) + (y * CHUNK_WIDTH) + x] = nullptr;
}
