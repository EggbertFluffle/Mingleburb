#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GLFW/glfw3.h>

#include "Globals.hpp"
#include "App.hpp"

App::App() :
	player(CHUNK_WIDTH / 2.0f, BUILD_HEIGHT / 2.0f, CHUNK_WIDTH / 2.0f, PI / 2.0f, 0.0f),
	gameManager(),
	graphicsManager()
{}

void App::init() {
	graphicsManager.shader.useShader();

	Block* b = gameManager.getBlock(-2, 0, 0);
	if(b == nullptr) {
		printf("block is nullptr\n");
	// } else if(b->id == 0) {
	// 	printf("block is air\n");
	} else {
		printf("block id is %d\n", b->id);
	}
}

void App::run() {
	while(!glfwWindowShouldClose(graphicsManager.window)) {
		if(player.inputManager.getKeyState(GLFW_KEY_Q)) {
			glfwSetWindowShouldClose(graphicsManager.window, true);
		}

		player.update(graphicsManager.window, &gameManager);

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		player.getLookAt(graphicsManager.view);
		graphicsManager.shader.setMat4("view", graphicsManager.view);
		graphicsManager.shader.setMat4("projection", graphicsManager.projection);

		for(int i = 0; i < 6; i++) {
			for(auto it = gameManager.chunks.begin(); it != gameManager.chunks.end(); it++) {
				graphicsManager.shader.setFloat("luminence", gameManager.faceLuminence[i]);
				graphicsManager.renderChunk(i, it);
			}
		}

		glfwSwapBuffers(graphicsManager.window);
		glfwPollEvents();
	}
}
