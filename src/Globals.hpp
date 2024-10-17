#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <GL/gl.h>
#define PI 3.14159f
#define TWO_PI PI * 2
#define HALF_PI (PI / 2.0f)
#define QUARTER_PI (HALF_PI / 2.0f)
#define THREE_QUARTERS_PI (QUARTER_PI * 3)

#include "Config.hpp"
#include "Player.hpp"
#include "GameManager.hpp"
#include "GraphicsManager.hpp"
#include <imgui/backends/imgui_impl_glfw.h>

inline GraphicsManager graphicsManager;
inline GameManager gameManager;
inline Player player((gameManager.worldWidth / 2.0f) * CHUNK_WIDTH - (CHUNK_WIDTH / 2.0f), 15, (gameManager.worldWidth / 2.0f) * CHUNK_WIDTH - (CHUNK_WIDTH / 2.0f), HALF_PI, 0.0f);;

inline void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	#ifdef DEBUG
	ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
	#endif

	player.inputManager.keyCallback(&key, &scancode, &action, &mods);
}

inline void mouseCallback(GLFWwindow* window, int button, int action, int mods) {
	#ifdef DEBUG
	ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
	#endif

	player.inputManager.mouseCallback(&button, &action, &mods);
}

inline void windowResizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	graphicsManager.texturedUIShader.setVec2("resolution", width, height);
}

#endif
