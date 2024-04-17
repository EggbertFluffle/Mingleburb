#pragma once

#include "GraphicsManager.hpp"
#include "GameManager.hpp"
#include "Player.hpp"

class App {
public:
	Player player;
	GameManager gameManager;
	GraphicsManager graphicsManager;

	App();
	void run();
	void init();
};
