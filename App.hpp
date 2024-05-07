#pragma once

#include "GraphicsManager.hpp"
#include "GameManager.hpp"
#include "Player.hpp"

class App {
public:
	GameManager gameManager;
	Player player;
	GraphicsManager graphicsManager;

	App();
	~App();
	void run();
	void init();
};
