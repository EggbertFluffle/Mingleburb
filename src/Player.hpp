#pragma once

#include <glm/glm.hpp>

#include "InputManager.hpp"

class Player {
	glm::vec3 velocity;
	float sensitivity;
	float speed;

public:
	InputManager inputManager;

	glm::vec3 position;
	float yaw;
	float pitch;
	bool mouseControls;

	Player();
	Player(float x, float y, float z, float h, float p);

	void update(GLFWwindow* window);
	void getLookAt(glm::mat4 &view);
	void propogateKeyCallback(GLFWwindow* window, int* key, int* scancode, int* action, int* mods);
	void moveLocal(float x, float y, float z);
	void moveWorld(float x, float y, float z);
};
