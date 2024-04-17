#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stdio.h>

#include "InputManager.hpp"
#include "Globals.hpp"

void InputManager::setKeyTrue(int key) {
	keyStates[key] = true;
}

void InputManager::setKeyFalse(int key) {
	keyStates[key] = false;
}

bool* InputManager::getKeyState(int key) {
	return &(keyStates[key]);
}

void InputManager::keyCallback(GLFWwindow* window, int* key, int* scancode, int* action, int* mods) {
	if (*action) {
		setKeyTrue(*key);
	} else {
		setKeyFalse(*key);
	}
}

void InputManager::captureCursor(GLFWwindow* window) {
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	deltaMouse.x = static_cast<float>(mouseX) - (WIDTH / 2.0f);
	deltaMouse.y = static_cast<float>(mouseY) - (HEIGHT / 2.0f);
	glfwSetCursorPos(window, static_cast<int>(WIDTH / 2), static_cast<int>(HEIGHT / 2));
}
