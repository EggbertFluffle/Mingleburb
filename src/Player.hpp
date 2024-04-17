#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "InputManager.hpp"
#include "GameManager.hpp"
#include "Block.hpp"

class Player {
	glm::vec3 velocity;
	float sensitivity;
	float speed;
	float viewDistance;

	Block* castBlockRay(GameManager* gameManager);

public:
	InputManager inputManager;

	glm::vec3 position;
	glm::vec3 lookDir;
	float yaw;
	float pitch;
	bool mouseControls;
	Block* selectedBlock;

	Player();
	Player(float x, float y, float z, float h, float p);

	void update(GLFWwindow* window, GameManager* gameManager);
	void getLookAt(glm::mat4 &view);
	void propogateKeyCallback(GLFWwindow* window, int* key, int* scancode, int* action, int* mods);
	void moveLocal(float x, float y, float z);
	void moveWorld(float x, float y, float z);
};
