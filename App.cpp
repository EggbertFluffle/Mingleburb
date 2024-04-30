#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GLFW/glfw3.h>

#include "Globals.hpp"
#include "App.hpp"

App::App() :
	gameManager(),
	player((gameManager.worldWidth / 2) * CHUNK_WIDTH, 15, (gameManager.worldWidth / 2) * CHUNK_WIDTH, PI / 2.0f, 0.0f),
	graphicsManager()
{}

void App::init() {
	graphicsManager.shader.useShader();
}

void App::run() {
	while(!glfwWindowShouldClose(graphicsManager.window)) {
		if(player.inputManager.getKeyState(GLFW_KEY_Q)) {
			glfwSetWindowShouldClose(graphicsManager.window, true);
		}

		player.update(graphicsManager.window, &gameManager);

		player.getLookAt(graphicsManager.view);

		graphicsManager.renderAllChunks(&gameManager, &player);

		glfwSwapBuffers(graphicsManager.window);
		glfwPollEvents();
	}
}
