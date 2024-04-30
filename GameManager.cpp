#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>
#include <forward_list>

#include "GameManager.hpp"
#include "Block.hpp"
#include "Globals.hpp"
#include "perlin.hpp"

GameManager::GameManager() : 
	po(Perlin::createPerlinOffsets(NOISE_OCTAVES))
{
	// for(int z = 0; z < 3; z++) {
	// 	for(int x = 0; x < 3; x++) {
	// 		chunks.push_front(Chunk(x, z));
	// 	}
	// }
	chunks.push_front(Chunk(0, 0));

	for(auto it = chunks.begin(); it != chunks.end(); it++) {
		it->generateNoise(po);	
	}

	for(auto it = chunks.begin(); it != chunks.end(); it++) {
		cullChunkFaces(&(*it));
	}

	glm::vec3 directionalLight(1, -0.5, 0);
	directionalLight = glm::normalize(directionalLight);
	float brightnessChop = 3.0f;
	faceLuminence[0] = (glm::dot(directionalLight, glm::vec3(1, 0, 0)) + 1) / brightnessChop;
	faceLuminence[1] = (glm::dot(directionalLight, glm::vec3(-1, 0, 0)) + 1) / brightnessChop;
	faceLuminence[2] = (glm::dot(directionalLight, glm::vec3(0, 1, 0)) + 1) / brightnessChop;
	faceLuminence[3] = (glm::dot(directionalLight, glm::vec3(0, -1, 0)) + 1) / brightnessChop;
	faceLuminence[4] = (glm::dot(directionalLight, glm::vec3(0, 0, 1)) + 1) / brightnessChop;
	faceLuminence[5] = (glm::dot(directionalLight, glm::vec3(0, 0, -1)) + 1) / brightnessChop;
}

void GameManager::cullFaces(int x, int y, int z) {
	Block* block = getBlock(x, y, z);
	if(block == nullptr || block->id == 0) return;
	block->faces = 0;
	
	// Right = 0b10000000
	Block* right = getBlock(x + 1, y, z);
	if (right == nullptr || right->id == 0) {
		block->faces = block->faces | 0b10000000;
	}

	// Left = 0b01000000
	Block* left = getBlock(x - 1, y, z);
	if(left == nullptr || left->id == 0) {
		block->faces = block->faces | 0b01000000;
	}

	// Top = 0b00100000
	Block* top = getBlock(x, y + 1, z);
	if (top == nullptr || top->id == 0) {
		block->faces = block->faces | 0b00100000;
	}

	// Bottom = 0b00010000
	Block* bottom = getBlock(x, y - 1, z);
	if (bottom == nullptr || bottom->id == 0) {
		block->faces = block->faces | 0b00010000;
	}

	// Back = 0b00001000
	Block* back = getBlock(x, y, z + 1);
	if (back == nullptr || back->id == 0) {
		block->faces = block->faces | 0b00001000;
	}

	// Front = 0b00000100
	Block* front = getBlock(x, y, z - 1);
	if (front == nullptr || front->id == 0) {
		block->faces = block->faces | 0b00000100;
	}

	printf("id: %d pos: (%d, %d, %d): %.8b\n",	block->id, x, y, z, block->faces);
	block->faces = ~block->faces;
}

void GameManager::cullChunkFaces(Chunk* chunk) {
	for(int z = 0; z < CHUNK_WIDTH; z++) {
		for(int y = 0; y < BUILD_HEIGHT; y++) {
			for(int x = 0; x < CHUNK_WIDTH; x++) {
				cullFaces(chunk->chunkCoordinates.x * CHUNK_WIDTH + x, y, chunk->chunkCoordinates.y * CHUNK_WIDTH + z);
			}
		}
	}
}

Block* GameManager::getBlock(int x, int y, int z) {
	Chunk* c = getChunk(int(x / CHUNK_WIDTH), int(z / CHUNK_WIDTH));
	return c != nullptr && y >= 0 && y < BUILD_HEIGHT - 1 ? c->getBlock(x % CHUNK_WIDTH, y, z % CHUNK_WIDTH) : nullptr;
}

Chunk* GameManager::getChunk(int x, int z) {
	for(std::forward_list<Chunk>::iterator it = chunks.begin(); it != chunks.end(); it++) {
		if(it->chunkCoordinates.x == x && it->chunkCoordinates.y == z) {
			return &(*it);
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