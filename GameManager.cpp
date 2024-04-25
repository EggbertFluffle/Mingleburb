#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <stdio.h>

#include "GameManager.hpp"
#include "Block.hpp"

GameManager::GameManager() {
	// glm::vec3 directionalLight(1, 0, 0);
	glm::vec3 directionalLight(1, -0.5, 0);
	directionalLight = glm::normalize(directionalLight);
	// Terrible name
	float brightnessChop = 3.0f;
	faceLuminence[0] = (glm::dot(directionalLight, glm::vec3(1, 0, 0)) + 1) / brightnessChop;
	faceLuminence[1] = (glm::dot(directionalLight, glm::vec3(-1, 0, 0)) + 1) / brightnessChop;
	faceLuminence[2] = (glm::dot(directionalLight, glm::vec3(0, 1, 0)) + 1) / brightnessChop;
	faceLuminence[3] = (glm::dot(directionalLight, glm::vec3(0, -1, 0)) + 1) / brightnessChop;
	faceLuminence[4] = (glm::dot(directionalLight, glm::vec3(0, 0, 1)) + 1) / brightnessChop;
	faceLuminence[5] = (glm::dot(directionalLight, glm::vec3(0, 0, -1)) + 1) / brightnessChop;

	for(int i = 0; i < 6; i++) {
		printf("%d: %f\n", i, faceLuminence[i]);
	}
}

void GameManager::cullFaces(int x, int y, int z) {
	Block* block = getBlock(x, y, z);
	if(block == nullptr) return;

	block->faces = 0b00000000;
	if(block->air) return;
	
	// Right = 0b10000000
	if (x != CHUNK_WIDTH - 1 && !blocks[z][y][x + 1].air) {
		block->faces = block->faces | 0b10000000;
	}
	
	// Left = 0b01000000
	if (x != 0 && !blocks[z][y][x - 1].air) {
		block->faces = block->faces | 0b01000000;
	}

	// Top = 0b00100000
	if (y != BUILD_HEIGHT - 1 && !blocks[z][y + 1][x].air) {
		block->faces = block->faces | 0b00100000;
	}
	
	// Bottom = 0b00010000
	if (y != 0 && !blocks[z][y - 1][x].air) {
		block->faces = block->faces | 0b00010000;
	}
	
	// Back = 0b00001000
	if (z != CHUNK_WIDTH - 1 && !blocks[z + 1][y][x].air) {
		block->faces = block->faces | 0b00001000;
	}

	// Front = 0b00000100
	if (z != 0 && !blocks[z - 1][y][x].air) {
		block->faces = block->faces | 0b00000100;
	}

	block->faces = ~block->faces;
}

Block* GameManager::getBlock(int x, int y, int z) {
	if (x < 0 || x > CHUNK_WIDTH - 1 || y < 0 || y > BUILD_HEIGHT - 1 || z < 0 || z > CHUNK_WIDTH - 1) {
		return nullptr;
	}
	return &(blocks[z][y][x]);
}

void GameManager::cullSurroundingBlocks(glm::vec3& selectedBlockCoords) {
	cullFaces(selectedBlockCoords.x + 1, selectedBlockCoords.y, selectedBlockCoords.z);
	cullFaces(selectedBlockCoords.x - 1, selectedBlockCoords.y, selectedBlockCoords.z);
	cullFaces(selectedBlockCoords.x, selectedBlockCoords.y + 1, selectedBlockCoords.z);
	cullFaces(selectedBlockCoords.x, selectedBlockCoords.y - 1, selectedBlockCoords.z);
	cullFaces(selectedBlockCoords.x, selectedBlockCoords.y, selectedBlockCoords.z + 1);
	cullFaces(selectedBlockCoords.x, selectedBlockCoords.y, selectedBlockCoords.z - 1);
}
