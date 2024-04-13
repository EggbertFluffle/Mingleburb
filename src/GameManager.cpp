#include <stdio.h>

#include "GameManager.hpp"
#include "Block.hpp"

GameManager::GameManager() {}

void GameManager::cullFaces(int x, int y, int z) {
	Block* block = &(blocks[z][y][x]);
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
