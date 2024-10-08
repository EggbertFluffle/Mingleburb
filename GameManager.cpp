#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>
#include <forward_list>

#include "GameManager.hpp"
#include "Block.hpp"
#include "perlin.hpp"

GameManager::GameManager() {
	po = Perlin::createPerlinOffsets(NOISE_OCTAVES);
	worldWidth = 2;
	for(unsigned int z = 0; z < worldWidth; z++) {
		for(unsigned int x = 0; x < worldWidth; x++) {
			chunks.emplace_front(Chunk(x, z));
		}
	}

	for(auto& c : chunks) {
		c.generateNoise(po);	
	}

	for(auto& c : chunks) {
		cullChunkFaces(&c);
	}

	glm::vec3 directionalLight(1, -0.5, 0);
	directionalLight = glm::normalize(directionalLight);
	const float brightnessChop = 3.0f;
	faceLuminence[0] = (glm::dot(directionalLight, glm::vec3(1, 0, 0)) + 1) / brightnessChop;
	faceLuminence[1] = (glm::dot(directionalLight, glm::vec3(-1, 0, 0)) + 1) / brightnessChop;
	faceLuminence[2] = (glm::dot(directionalLight, glm::vec3(0, 1, 0)) + 1) / brightnessChop;
	faceLuminence[3] = (glm::dot(directionalLight, glm::vec3(0, -1, 0)) + 1) / brightnessChop;
	faceLuminence[4] = (glm::dot(directionalLight, glm::vec3(0, 0, 1)) + 1) / brightnessChop;
	faceLuminence[5] = (glm::dot(directionalLight, glm::vec3(0, 0, -1)) + 1) / brightnessChop;
}

void GameManager::cullFaces(const int x, const int y, const int z) {
	Block* const block = getBlock(x, y, z);
	unsigned char faces = 0;
	if(block == nullptr || block->id == 0) return;
	const std::array<Block* const, 6> dirs {
		getBlock(x + 1, y, z),
		getBlock(x - 1, y, z),
		getBlock(x, y + 1, z),
		getBlock(x, y - 1, z),
		getBlock(x, y, z + 1),
		getBlock(x, y, z - 1)
	};

	for(std::uint8_t i = 0; i < 6; i++) {
		const unsigned char f = 0b10000000 >> (i);
		Block* const b = dirs.at(i);
		if (b == nullptr || (b != nullptr && b->id != 0)) {
			faces = faces | f;
		}
	}
	faces = ~faces;

	block->faces = faces;
}

void GameManager::cullChunkFaces(Chunk* chunk) {
	for(int z = 0; z < CHUNK_WIDTH; z++) {
		for(int y = 0; y < BUILD_HEIGHT; y++) {
			for(int x = 0; x < CHUNK_WIDTH; x++) {
				cullFaces(chunk->coords.x * CHUNK_WIDTH + x, y, chunk->coords.y * CHUNK_WIDTH + z);
			}
		}
	}
}

Block* const GameManager::getBlock(const int x, const int y, const int z) {
	if(x < 0 || y < 0 || z < 0) return nullptr;
	Chunk* const c = getChunk(int(x / CHUNK_WIDTH), int(z / CHUNK_WIDTH));
	return c != nullptr && y < BUILD_HEIGHT ? c->getBlock(x % CHUNK_WIDTH, y, z % CHUNK_WIDTH) : nullptr;
}

Chunk* const GameManager::getChunk(const int x, const int z) {
	for(auto& c : chunks) {
		if(c.coords.x == x && c.coords.y == z) {
			return &c;
		}
	}
	return nullptr;
}

void GameManager::cullSurroundingBlocks(glm::vec3& selectedBlockCoords) {
	cullFaces(selectedBlockCoords.x + 1, selectedBlockCoords.y, selectedBlockCoords.z);
	cullFaces(selectedBlockCoords.x - 1, selectedBlockCoords.y, selectedBlockCoords.z);
	cullFaces(selectedBlockCoords.x, selectedBlockCoords.y + 1, selectedBlockCoords.z);
	cullFaces(selectedBlockCoords.x, selectedBlockCoords.y - 1, selectedBlockCoords.z);
	cullFaces(selectedBlockCoords.x, selectedBlockCoords.y, selectedBlockCoords.z + 1);
	cullFaces(selectedBlockCoords.x, selectedBlockCoords.y, selectedBlockCoords.z - 1);
}
