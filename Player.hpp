#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "InputManager.hpp"
#include "Block.hpp"

class Player {
	glm::vec3 velocity;
	float sensitivity;
	float speed;
	float viewDistance;
	double previousTime;

	void castBlockRay();

public:
	InputManager inputManager;

	glm::vec3 position;
	glm::vec3 lookDir;
	float yaw;
	float pitch;
	Block* selectedBlock;
	glm::vec3 selectedBlockCoords;

	Player();
	Player(const float x, const float y, const float z, const float h, const float p);

	void update(float& deltaTime);
	void getLookAt(glm::mat4& view);
	void moveLocal(const float x, const float y, const float z, const float& deltaTime);
	void moveWorld(const float x, const float y, const float z);
};
