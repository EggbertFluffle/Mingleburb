#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#define PI 3.14159f
#define TWO_PI PI * 2
#define HALF_PI (PI / 2.0f)
#define QUARTER_PI (HALF_PI / 2.0f)
#define THREE_QUARTERS_PI (QUARTER_PI * 3)

#include "Config.hpp"
#include "Player.hpp"
#include "GameManager.hpp"
#include "GraphicsManager.hpp"

inline GraphicsManager graphicsManager;
inline GameManager gameManager;
inline Player player((gameManager.worldWidth / 2) * CHUNK_WIDTH, 15, (gameManager.worldWidth / 2) * CHUNK_WIDTH, HALF_PI, 0.0f);;

inline void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	player.inputManager.keyCallback(&key, &scancode, &action, &mods);
}

inline void mouseCallback(GLFWwindow* window, int button, int action, int mods) {
	player.inputManager.mouseCallback(&button, &action, &mods);
}

#endif
