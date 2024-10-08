#pragma once

#include <map>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class InputManager {
	std::map<int, bool> keyStates;
	glm::vec2 previousMousePos;

	bool mouseButton1Down = false;
	bool mouseButton2Down = false;
	bool mouseButton1Pressed = false;
	bool mouseButton2Pressed = false;

public: 
	glm::vec2 deltaMouse;

	void keyCallback(int* key, int* scancode, int* action, int* mods);
	void mouseCallback(int* button, int* action, int* mods);
	void captureCursor(GLFWwindow* window);

	void setKeyTrue(const int key);
	void setKeyFalse(const int key);

	bool getKeyState(const int key) const;
	bool getMouseButtonDown(const int button) const;
	bool getMouseButtonPressed(const int button);
};

