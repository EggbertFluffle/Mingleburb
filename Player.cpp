#include <GLFW/glfw3.h>

#include <glm/common.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <sys/select.h>

#include "Player.hpp"
#include "InputManager.hpp"
#include "Block.hpp"
#include "Globals.hpp"

Player::Player(float x, float y, float z, float h, float p) :
	sensitivity(0.05f),
	speed(10000.0f),
	viewDistance(5.0f),
	position(x, y, z),
	yaw(h),
	pitch(p)
{
	glfwSetKeyCallback(graphicsManager.window, (GLFWkeyfun)keyCallback);
	glfwSetMouseButtonCallback(graphicsManager.window, (GLFWmousebuttonfun)mouseCallback);
}

void Player::update(float& deltaTime) {
	// Quit if Q is pressed
	if(player.inputManager.getKeyState(GLFW_KEY_Q)) {
		glfwSetWindowShouldClose(graphicsManager.window, true);
	}

	inputManager.captureCursor(graphicsManager.window);

	castBlockRay();
	if(selectedBlock != nullptr) {
		selectedBlock->highlighted = true;
		if(inputManager.getMouseButtonPressed(GLFW_MOUSE_BUTTON_1)) {
			*selectedBlock = Block();
			gameManager.cullSurroundingBlocks(selectedBlockCoords);
		}
	}

	velocity = glm::vec3(
		(inputManager.getKeyState(GLFW_KEY_D) ? 1.0f : 0.0f) + (inputManager.getKeyState(GLFW_KEY_A) ? -1.0f : 0.0f),
		(inputManager.getKeyState(GLFW_KEY_SPACE) ? 1.0f : 0.0f) + (inputManager.getKeyState(GLFW_KEY_LEFT_SHIFT) ? -1.0f : 0.0f),
		(inputManager.getKeyState(GLFW_KEY_W) ? 1.0f : 0.0f) + (inputManager.getKeyState(GLFW_KEY_S) ? -1.0f : 0.0f)
	);

	moveLocal(velocity.x, velocity.y, velocity.z, deltaTime);

	// Use mouse distance if MOUSE_CONTROLS are enables, and arrow keys otherwise
	if(MOUSE_CONTROLS) {
		yaw += inputManager.deltaMouse.x / WIDTH;
		pitch -= inputManager.deltaMouse.y / HEIGHT;
	} else {
		yaw += (inputManager.getKeyState(GLFW_KEY_RIGHT) ? 0.05f : 0.0f) + (inputManager.getKeyState(GLFW_KEY_LEFT) ? -0.05f : 0.0f);
		pitch += (inputManager.getKeyState(GLFW_KEY_UP) ? 0.05f : 0.0f) + (inputManager.getKeyState(GLFW_KEY_DOWN) ? -0.05f : 0.0f);
	}
	yaw = yaw > TWO_PI ? TWO_PI - yaw : (yaw < 0.0f ? TWO_PI + yaw : yaw);

	if(pitch > HALF_PI - 0.1f) pitch = HALF_PI - 0.1f;
	if(pitch < -HALF_PI + 0.1f) pitch = -HALF_PI + 0.1f;
}

void Player::moveWorld(const float x, const float y, const float z) {
	position += glm::vec3(x, y, z); 
}

void Player::moveLocal(const float x, const float y, const float z, const float& deltaTime) {
	moveWorld(
		(std::cos(yaw) * z + std::cos(yaw + HALF_PI) * x) * speed * deltaTime,
		y * speed * deltaTime,
		(std::sin(yaw) * z + std::sin(yaw + HALF_PI) * x) * speed * deltaTime
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

// TODO: Rewrite this to include face data
void Player::castBlockRay() {
	Block* block;
	for(float a = 0; a < 1.0f; a += 0.01f) {
		glm::vec3 reach(
			position.x + (lookDir.x * viewDistance) * a,
			position.y + (lookDir.y * viewDistance) * a,
			position.z + (lookDir.z * viewDistance) * a
		);
		block = gameManager.getBlock(
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
