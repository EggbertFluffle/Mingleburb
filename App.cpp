#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GLFW/glfw3.h>

#include "Globals.hpp"
#include "App.hpp"

App::App() :
	player(CHUNK_WIDTH * 3 / 2, 10, CHUNK_WIDTH * 3 / 2, PI / 2.0f, 0.0f),
	gameManager(),
	graphicsManager()
{}

void App::init() {
	graphicsManager.shader.useShader();
}

void App::run() {
	while(!glfwWindowShouldClose(graphicsManager.window)) {
		glfwPollEvents();

		if(player.inputManager.getKeyState(GLFW_KEY_Q)) {
			glfwSetWindowShouldClose(graphicsManager.window, true);
		}

		player.update(graphicsManager.window, &gameManager);

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		player.getLookAt(graphicsManager.view);
		graphicsManager.shader.setMat4("view", graphicsManager.view);
		graphicsManager.shader.setMat4("projection", graphicsManager.projection);

		graphicsManager.renderAllChunks(&gameManager);

		glfwSwapBuffers(graphicsManager.window);

		// if(graphicsManager.highlightedBlock == nullptr) graphicsManager.highlightedBlock->highlighted = false;
	}
}
