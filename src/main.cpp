// GLAD is responsible for making the correct function bindings for OpenGL
#include <glad/glad.h>

// GLFW is responsible for windowing and input handling
#include <GLFW/glfw3.h>

// stb_image is a popular image loading library
#include "GameManager.hpp"
#include "stb_image.hpp"

// glm is used tomake matrix and general graphics math easy
#include <glm/glm.hpp>

#include <stdio.h>
#include <stdbool.h>

#include "Shader.hpp"
#include "Player.hpp"
#include "GraphicsManager.hpp"
#include "GameManager.hpp"
#include "Globals.hpp"

#define WIDTH 800
#define HEIGHT 600
#define PI 3.14159

const char* fragmentShaderPath = "./src/shaders/fragment.glsl";
const char* vertexShaderPath = "./src/shaders/vertex.glsl";

int InitializeGLFW(GLFWwindow* &window);

void windowResizeCallback(GLFWwindow* window, int width, int height);
void propogateKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
// void propogateCursorCallback(GLFWwindow*, double x, double y);

Player player(CHUNK_WIDTH / 2.0f, BUILD_HEIGHT / 2.0f, CHUNK_WIDTH / 2.0f, PI / 2.0f, 0.0f);

int main() {
	GLFWwindow* window;
	if(InitializeGLFW(window) == -1) return -1;


	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize GLAD\n");
		return -1;
	} 

	GraphicsManager graphicsManager;
	graphicsManager.loadTexture("dirt", "./src/assets/dirt.png");
	graphicsManager.loadTexture("pink_wool", "./src/assets/pink_wool.png");
	graphicsManager.loadTexture("oak_planks", "./src/assets/oak_planks.png");

	Shader shader(vertexShaderPath, fragmentShaderPath);

	glm::mat4 view;
	glm::mat4 projection = glm::perspective(glm::radians(75.0f), (float)WIDTH/(float)HEIGHT, 0.1f, 100.1f);

	GameManager gameManager;

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

	// Render loop
	while(!glfwWindowShouldClose(window)) {
		player.update(window);

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		player.getLookAt(view);

		shader.setMat4("view", view);
		shader.setMat4("projection", projection);

		shader.useShader();

		for(int i = 1; i <= 6; i++) {
			graphicsManager.bindFace(i - 1);
			unsigned char face = 0b00000100 << (6 - i);
			for(int z = 0; z < CHUNK_WIDTH - 1; z++) {
				for(int y = 0; y < BUILD_HEIGHT - 1; y++) {
					for(int x = 0; x < CHUNK_WIDTH - 1; x++) {
						if(!gameManager.blocks[z][y][x].air && (gameManager.blocks[z][y][x].faces & face) == face) {
							glm::mat4 model(1.0f);
							model = glm::translate(model, glm::vec3(
								static_cast<float>(x),
								static_cast<float>(y),
								static_cast<float>(z)
							));
							model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

							shader.setMat4("model", model);

							graphicsManager.bindTexture(gameManager.blocks[z][y][x].texture);

							glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
						}
					}
				}
			}
		}

		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();    
	}

	glfwTerminate();

	return 0;
}

int InitializeGLFW(GLFWwindow* &window) {
	glfwInit();
	// Set some options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Mingelburb", NULL, NULL);
	if (window == NULL) {
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, windowResizeCallback);
	glfwSetKeyCallback(window, propogateKeyCallback);

	return 0;
}

void windowResizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void propogateKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	player.propogateKeyCallback(window, &key, &scancode, &action, &mods);
}
