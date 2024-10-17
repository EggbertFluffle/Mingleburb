#pragma once

#include <map>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class InputManager {
	glm::vec2 previousMousePos;

	bool mouseButton1Down = false;
	bool mouseButton2Down = false;
	bool mouseButton1Pressed = false;
	bool mouseButton2Pressed = false;

public: 
	std::map<int, bool> keyStates;
	std::map<int, bool> keyPresses;
	glm::vec2 deltaMouse;

	void updatePressed();

	void keyCallback(int* key, int* scancode, int* action, int* mods);
	void mouseCallback(int* button, int* action, int* mods);
	void captureCursor(GLFWwindow* window);

	void setKeyState(const int*, const int* action);

	bool getKeyState(const int key) const;
	bool getKeyPressed(const int key);
	bool getMouseButtonDown(const int button) const;
	bool getMouseButtonPressed(const int button);
};

