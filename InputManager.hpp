#pragma once

#include <map>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class InputManager {
	std::map<int, bool> keyStates;
	glm::vec2 previousMousePos;
	bool mouseButton1, mouseButton2;

public: 
	glm::vec2 deltaMouse;

	void keyCallback(GLFWwindow* window, int* key, int* scancode, int* action, int* mods);
	void mouseCallback(GLFWwindow* window, int* button, int* action, int* mods);
	void captureCursor(GLFWwindow* window);

	void setKeyTrue(int key);
	void setKeyFalse(int key);

	bool getKeyState(int key);
	bool getMouseButton(int button);
};

