#include <GLFW/glfw3.h>

#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>

#include "Player.hpp"
#include "InputManager.hpp"
#include "Globals.hpp"

#define PI 3.14159

Player::Player() :
	speed(0.1f),
	sensitivity(0.05f)
{}

Player::Player(float x, float y, float z, float h, float p) :
	position(x, y, z),
	yaw(h),
	pitch(p),
	speed(0.1f),
	sensitivity(0.05f),
	mouseControls(MOUSE_CONTROLS)
{}

void Player::update(GLFWwindow* window) {
	inputManager.captureCursor(window);

	velocity = glm::vec3(
		(*(inputManager.getKeyState(GLFW_KEY_D)) ? 1.0f : 0.0f) + (*(inputManager.getKeyState(GLFW_KEY_A)) ? -1.0f : 0.0f),
		(*(inputManager.getKeyState(GLFW_KEY_SPACE)) ? 1.0f : 0.0f) + (*(inputManager.getKeyState(GLFW_KEY_LEFT_SHIFT)) ? -1.0f : 0.0f),
		(*(inputManager.getKeyState(GLFW_KEY_W)) ? 1.0f : 0.0f) + (*(inputManager.getKeyState(GLFW_KEY_S)) ? -1.0f : 0.0f)
	);

	moveLocal(velocity.x, velocity.y, velocity.z);
	 
	if(MOUSE_CONTROLS) {
		yaw += inputManager.deltaMouse.x / WIDTH;
	} else {
		yaw += (*(inputManager.getKeyState(GLFW_KEY_RIGHT)) ? 0.05f : 0.0f) + (*(inputManager.getKeyState(GLFW_KEY_LEFT)) ? -0.05f : 0.0f);
		pitch += (*(inputManager.getKeyState(GLFW_KEY_UP)) ? 0.05f : 0.0f) + (*(inputManager.getKeyState(GLFW_KEY_DOWN)) ? -0.05f : 0.0f);
	}

	if(pitch > PI / 2) pitch = PI / 2;
	if(pitch < -PI / 2) pitch = PI / -2;
}

void Player::moveWorld(float x, float y, float z) {
	position += glm::vec3(x, y, z); 
}

void Player::moveLocal(float x, float y, float z) {
	moveWorld(
		(std::cos(yaw) * z + std::cos(yaw + PI / 2) * x) * speed,
		y * speed,
		(std::sin(yaw) * z + std::sin(yaw + PI / 2) * x) * speed
	);
}

void Player::getLookAt(glm::mat4 &view) {
	view = glm::lookAt(
		position,
		glm::vec3(position.x + std::cos(yaw), position.y + std::tan(pitch), position.z + std::sin(yaw)),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
}

void Player::propogateKeyCallback(GLFWwindow* window, int* key, int* scancode, int* action, int* mods) {
	inputManager.keyCallback(window, key, scancode, action, mods);
}
