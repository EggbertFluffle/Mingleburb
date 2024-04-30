#include <GLFW/glfw3.h>

#include <glm/common.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>

#include "Player.hpp"
#include "InputManager.hpp"
#include "Block.hpp"
#include "Globals.hpp"

Player::Player() :
	sensitivity(0.05f),
	speed(0.1f),
	viewDistance(5.0f) {}

Player::Player(float x, float y, float z, float h, float p) :
	sensitivity(0.05f),
	speed(15.0f),
	viewDistance(5.0f),
	position(x, y, z),
	yaw(h),
	pitch(p),
	mouseControls(MOUSE_CONTROLS)
{}

void Player::update(GLFWwindow* window, GameManager* gameManager) {
	deltaTime = glfwGetTime() - previousTime;

	inputManager.captureCursor(window);

	castBlockRay(gameManager);
	if(selectedBlock != nullptr) {
		selectedBlock->highlighted = true;
		if(inputManager.getMouseButton(GLFW_MOUSE_BUTTON_1)) {
			*selectedBlock = Block();
			gameManager->cullSurroundingBlocks(selectedBlockCoords);
		}
	}

	velocity = glm::vec3(
		(inputManager.getKeyState(GLFW_KEY_D) ? 1.0f : 0.0f) + (inputManager.getKeyState(GLFW_KEY_A) ? -1.0f : 0.0f),
		(inputManager.getKeyState(GLFW_KEY_SPACE) ? 1.0f : 0.0f) + (inputManager.getKeyState(GLFW_KEY_LEFT_SHIFT) ? -1.0f : 0.0f),
		(inputManager.getKeyState(GLFW_KEY_W) ? 1.0f : 0.0f) + (inputManager.getKeyState(GLFW_KEY_S) ? -1.0f : 0.0f)
	);

	moveLocal(velocity.x, velocity.y, velocity.z);
	 
	if(MOUSE_CONTROLS) {
		yaw += inputManager.deltaMouse.x / WIDTH;
		pitch -= inputManager.deltaMouse.y / HEIGHT;
	} else {
		yaw += (inputManager.getKeyState(GLFW_KEY_RIGHT) ? 0.05f : 0.0f) + (inputManager.getKeyState(GLFW_KEY_LEFT) ? -0.05f : 0.0f);
		pitch += (inputManager.getKeyState(GLFW_KEY_UP) ? 0.05f : 0.0f) + (inputManager.getKeyState(GLFW_KEY_DOWN) ? -0.05f : 0.0f);
	}

	if(pitch > PI / 2) pitch = PI / 2;
	if(pitch < -PI / 2) pitch = PI / -2;

	previousTime = glfwGetTime();
}

void Player::moveWorld(float x, float y, float z) {
	position += glm::vec3(x, y, z); 
}

void Player::moveLocal(float x, float y, float z) {
	moveWorld(
		(std::cos(yaw) * z + std::cos(yaw + PI / 2) * x) * speed * deltaTime,
		y * speed * deltaTime,
		(std::sin(yaw) * z + std::sin(yaw + PI / 2) * x) * speed * deltaTime
	);
}

void Player::getLookAt(glm::mat4 &view) {
	lookDir = glm::normalize(glm::vec3(std::cos(yaw), std::tan(pitch), std::sin(yaw)));
	view = glm::lookAt(
		position,
		position + lookDir,
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
}

void Player::propogateKeyCallback(GLFWwindow* window, int* key, int* scancode, int* action, int* mods) {
	inputManager.keyCallback(window, key, scancode, action, mods);
}

void Player::propogateMouseCallback(GLFWwindow* window, int* button, int* action, int* mods) {
	inputManager.mouseCallback(window, button, action, mods);
}

void Player::castBlockRay(GameManager* gameManager) {
	Block* block;
	for(float a = 0; a < 1.0f; a += 0.01f) {
		glm::vec3 reach(
			position.x + (lookDir.x * viewDistance) * a,
			position.y + (lookDir.y * viewDistance) * a,
			position.z + (lookDir.z * viewDistance) * a
		);
		block = gameManager->getBlock(
			int(reach.x + 0.5),
			int(reach.y + 0.5),
			int(reach.z + 0.5)
		);
		if(block != nullptr && block->id != 0) {
			selectedBlock = block; 
			selectedBlockCoords = glm::vec3(
				std::floor(reach.x + 0.5),
				std::floor(reach.y + 0.5),
				std::floor(reach.z + 0.5)
			);
			return;
		}
	}
	selectedBlock = nullptr;
}
