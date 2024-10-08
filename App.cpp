#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GLFW/glfw3.h>

#include "Globals.hpp"
#include "App.hpp"

void App::init() {
	graphicsManager.shader.useShader();
}

void App::run() {
	while(!glfwWindowShouldClose(graphicsManager.window)) {
		glfwPollEvents();

		deltaTime = glfwGetTime() - previousTime;

		player.update(deltaTime);

		player.getLookAt(graphicsManager.view);

		graphicsManager.renderAllChunks();

		glfwSwapBuffers(graphicsManager.window);

		previousTime = glfwGetTime();
	}
}
