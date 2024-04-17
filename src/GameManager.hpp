#pragma once

#include "Block.hpp"
#include "Globals.hpp"

class GameManager {
public:
	Block blocks[CHUNK_WIDTH][BUILD_HEIGHT][CHUNK_WIDTH];

	GameManager();
	void cullFaces(int x, int y, int z);
	Block* getBlock(int x, int y, int z);
};
