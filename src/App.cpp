#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Globals.hpp"
#include "App.hpp"

App::App() :
	player(CHUNK_WIDTH / 2.0f, BUILD_HEIGHT / 2.0f, CHUNK_WIDTH / 2.0f, PI / 2.0f, 0.0f),
	gameManager(),
	graphicsManager()
{}

void App::init() {
	for(int z = 0; z < CHUNK_WIDTH - 1; z++) {
		for(int y = 0; y < BUILD_HEIGHT - 1; y++) {
			for(int x = 0; x < CHUNK_WIDTH - 1; x++) {
				if (y < 32) gameManager.blocks[z][y][x] = Block("dirt");
			}
		}
	}

	for(int z = 0; z < CHUNK_WIDTH - 1; z++) {
		for(int y = 0; y < BUILD_HEIGHT - 1; y++) {
			for(int x = 0; x < CHUNK_WIDTH - 1; x++) {
				gameManager.cullFaces(x, y, z);
			}
		}
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

		for(int i = 1; i <= 6; i++) {
			graphicsManager.bindFace(i - 1);
			unsigned char face = 0b00000100 << (6 - i);
			for(int z = 0; z < CHUNK_WIDTH; z++) {
				for(int y = 0; y < BUILD_HEIGHT; y++) {
					for(int x = 0; x < CHUNK_WIDTH; x++) {
						Block* curr = gameManager.getBlock(x, y, z);
						if(!curr->air && (curr->faces & face) == face) {
							glm::mat4 model(1.0f);
							model = glm::scale(
								glm::translate(glm::mat4(1.0f), glm::vec3(
									static_cast<float>(x),
									static_cast<float>(y),
									static_cast<float>(z)
								)),
								glm::vec3(0.5f, 0.5f, 0.5f)
							);
							graphicsManager.shader.setMat4("model", model);
							graphicsManager.shader.setMat4("projection", graphicsManager.projection);
							graphicsManager.shader.setInt("highlighted", curr->highlighted);
							graphicsManager.shader.useShader();
							graphicsManager.bindTexture(curr->texture);

							glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
						}
					}
				}
			}
		}

		for(int z = 0; z < CHUNK_WIDTH - 1; z++) {
			for(int y = 0; y < BUILD_HEIGHT - 1; y++) {
				for(int x = 0; x < CHUNK_WIDTH - 1; x++) {
					gameManager.blocks[z][y][x].highlighted = false;
				}
			}
		}

		glfwSwapBuffers(graphicsManager.window);
		glfwPollEvents();
	}
}
