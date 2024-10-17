#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <glm/common.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <sys/select.h>

#include "Player.hpp"
#include "InputManager.hpp"
#include "Block.hpp"
#include "Globals.hpp"
#include "Config.hpp"

#define IM_GUI_VEC(name, vec) ImGui::Text("%s: (%.3f, %.3f, %.3f)", name, vec.x, vec.y, vec.z)

Player::Player(float x, float y, float z, float h, float p) :
	sensitivity(0.05f),
	speed(10.0f),
	viewDistance(5.0f),
	position(x, y, z),
	yaw(h),
	pitch(p)
{
	glfwSetKeyCallback(graphicsManager.window, (GLFWkeyfun)keyCallback);
	glfwSetMouseButtonCallback(graphicsManager.window, (GLFWmousebuttonfun)mouseCallback);
}

void Player::update(float& deltaTime) {
	// Quit the game if Q is pressed
	if(player.inputManager.getKeyState(GLFW_KEY_Q)) {
		glfwSetWindowShouldClose(graphicsManager.window, true);
	}

	// Toggle the mouse to be on or off depending on if the escape key is pressed
	if(player.inputManager.getKeyPressed(GLFW_KEY_ESCAPE)) {
		mouseFree = !mouseFree;
	}

	// Get mouse travel
	if(!mouseFree) inputManager.captureCursor(graphicsManager.window);

	// Get information about block under cursor
	castBlockRay();

	// If we find a block check for break or place action
	if(selectedBlock != nullptr && selectedBlock->id != 0) {
		selectedBlock->highlighted = true;

		if(inputManager.getMouseButtonPressed(GLFW_MOUSE_BUTTON_1)) { // Break block
			*selectedBlock = Block();
			gameManager.cullSurroundingBlocks(selectedBlockCoords);
		} else if(inputManager.getMouseButtonPressed(GLFW_MOUSE_BUTTON_2)) { // PLACE block
			glm::vec3 placedBlockCoords = *selectedNormal + selectedBlockCoords;

			gameManager.setBlock(placedBlockCoords, 2);
			gameManager.cullSurroundingBlocks(placedBlockCoords);
			gameManager.cullFaces(placedBlockCoords);
		}
	}

	ImGui::DragFloat("Speed", &speed);

	// Translate inputs into a direction with speed by deltaTime
	velocity = glm::vec3(
		(inputManager.getKeyState(GLFW_KEY_D) ? 1.0f : 0.0f) + (inputManager.getKeyState(GLFW_KEY_A) ? -1.0f : 0.0f),
		(inputManager.getKeyState(GLFW_KEY_SPACE) ? 1.0f : 0.0f) + (inputManager.getKeyState(GLFW_KEY_LEFT_SHIFT) ? -1.0f : 0.0f),
		(inputManager.getKeyState(GLFW_KEY_W) ? 1.0f : 0.0f) + (inputManager.getKeyState(GLFW_KEY_S) ? -1.0f : 0.0f)
	) * speed * deltaTime;

	moveLocal(velocity.x, velocity.y, velocity.z, deltaTime);

	// Use mouse distance if MOUSE_CONTROLS are enables, and arrow keys otherwise
	if(!mouseFree) {
		yaw += inputManager.deltaMouse.x / WIDTH;
		pitch -= inputManager.deltaMouse.y / HEIGHT;
	} else {
		yaw += (inputManager.getKeyState(GLFW_KEY_RIGHT) ? 0.05f : 0.0f) + (inputManager.getKeyState(GLFW_KEY_LEFT) ? -0.05f : 0.0f);
		pitch += (inputManager.getKeyState(GLFW_KEY_UP) ? 0.05f : 0.0f) + (inputManager.getKeyState(GLFW_KEY_DOWN) ? -0.05f : 0.0f);
	}

	ImGui::SliderFloat("Yaw", &yaw, 0, TWO_PI, "%.3f");
	ImGui::SliderFloat("Pitch", &pitch, -HALF_PI + 0.01f, HALF_PI + 0.01f, "%.3f");

	// Clamp pitch to avoid gimbal lock and wrap yaw
	if(pitch > HALF_PI - 0.1f) pitch = HALF_PI - 0.1f;
	if(pitch < -HALF_PI + 0.1f) pitch = -HALF_PI + 0.1f;
	yaw = yaw > TWO_PI ? TWO_PI - yaw : (yaw < 0.0f ? TWO_PI + yaw : yaw);

	ImGui::Text("Delta time: %f", deltaTime);

	inputManager.updatePressed();
}

void Player::moveWorld(const float x, const float y, const float z) {
	position += glm::vec3(x, y, z); 
}

void Player::moveLocal(const float x, const float y, const float z, const float& deltaTime) {
	moveWorld(
		(std::cos(yaw) * z + std::cos(yaw + HALF_PI) * x),
		y,
		(std::sin(yaw) * z + std::sin(yaw + HALF_PI) * x) 
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

void Player::castBlockRay() {
	selectedBlock = nullptr;
	
	// Step across whole x coordinates
	glm::vec3 stepX = lookDir / std::abs(lookDir.x);
	
	// Difference of position to closest whole x value that the player is facing
	float nearestX = (stepX.x > 0 ? std::ceil(position.x) : std::floor(position.x)) - position.x;
	Block* blockX = nullptr;
	glm::vec3 currX = position + (stepX.x * (nearestX * stepX));
	
	for(int i = 0; glm::length(currX - position) < viewDistance; i++) {
		blockX = gameManager.getBlockFloored(currX.x - (stepX.x < 0 ? 1 : 0), currX.y, currX.z);
		if(blockX != nullptr && blockX->id != 0) { break; }
		currX += stepX;
	}
	float distanceX = glm::length(currX - position);

	// Step across whole y coordinates
	glm::vec3 stepY = lookDir / std::abs(lookDir.y);
	float nearestY = (stepY.y > 0 ? std::ceil(position.y) : std::floor(position.y)) - position.y;
	Block* blockY = nullptr;
	glm::vec3 currY = position + (stepY.y * (nearestY * stepY));
	
	for(int i = 0; glm::length(currY - position) < viewDistance; i++) {
		blockY = gameManager.getBlockFloored(currY.x, currY.y - (stepY.y < 0 ? 1 : 0), currY.z);
		if(blockY != nullptr && blockY->id != 0) { break; }
		currY += stepY;
	}
	float distanceY = glm::length(currY - position);

	// Step across whole z coordinates
	glm::vec3 stepZ = lookDir / std::abs(lookDir.z);
	float nearestZ = (stepZ.z > 0 ? std::ceil(position.z) : std::floor(position.z)) - position.z;
	Block* blockZ = nullptr;
	glm::vec3 currZ = position + (stepZ.z * (nearestZ * stepZ));
	
	for(int i = 0; glm::length(currZ - position) < 10.0f; i++) {
		blockZ = gameManager.getBlockFloored(currZ.x, currZ.y, currZ.z - (stepZ.z < 0 ? 1 : 0));
		if(blockZ != nullptr && blockZ->id != 0) { break; }
		currZ += stepZ;
	}
	float distanceZ = glm::length(currZ - position);

	if(blockX != nullptr && (distanceX < distanceY && distanceX < distanceZ)) {
		selectedBlock = blockX;
		selectedNormal = stepX.x > 0 ? &BLOCK_NORMAL::NEGATIVE_X : &BLOCK_NORMAL::POSITIVE_X;
		selectedBlockCoords.x = std::floor(currX.x - (stepX.x < 0 ? 1 : 0));
		selectedBlockCoords.y = std::floor(currX.y);
		selectedBlockCoords.z = std::floor(currX.z);
		return;
	}

	if(blockY != nullptr && (distanceY < distanceX && distanceY < distanceZ)) {
		selectedBlock = blockY;
		selectedNormal = stepY.y > 0 ? &BLOCK_NORMAL::NEGATIVE_Y : &BLOCK_NORMAL::POSITIVE_Y;
		selectedBlockCoords.x = std::floor(currY.x);
		selectedBlockCoords.y = std::floor(currY.y - (stepY.y < 0 ? 1 : 0));
		selectedBlockCoords.z = std::floor(currY.z);
		return;
	}

	if(blockZ != nullptr && (distanceZ < distanceX && distanceZ < distanceY)) {
		selectedBlock = blockZ;
		selectedNormal = stepZ.z > 0 ? &BLOCK_NORMAL::NEGATIVE_Z : &BLOCK_NORMAL::POSITIVE_Z;
		selectedBlockCoords.x = std::floor(currZ.x);
		selectedBlockCoords.y = std::floor(currZ.y);
		selectedBlockCoords.z = std::floor(currZ.z - (stepZ.z < 0 ? 1 : 0));
		return;
	}
}
