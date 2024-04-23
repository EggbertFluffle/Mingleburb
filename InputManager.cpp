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

bool InputManager::getKeyState(int key) {
	return keyStates[key];
}

bool InputManager::getMouseButton(int button) {
	switch(button) {
		case GLFW_MOUSE_BUTTON_1:
			return mouseButton1;
			break;
		case GLFW_MOUSE_BUTTON_2:
			return mouseButton2;
			break;
		default: 
			return false;
			break;
	}
}

void InputManager::keyCallback(GLFWwindow* window, int* key, int* scancode, int* action, int* mods) {
	if (*action) {
		setKeyTrue(*key);
	} else {
		setKeyFalse(*key);
	}
}

void InputManager::mouseCallback(GLFWwindow* window, int* button, int* action, int* mods) {
	switch(*button) {
		case GLFW_MOUSE_BUTTON_1:
			mouseButton1 = *action;
			break;
		case GLFW_MOUSE_BUTTON_2:
			mouseButton2 = *action;
			break;
	}
}

void InputManager::captureCursor(GLFWwindow* window) {
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	deltaMouse.x = static_cast<float>(mouseX) - (WIDTH / 2.0f);
	deltaMouse.y = static_cast<float>(mouseY) - (HEIGHT / 2.0f);
	glfwSetCursorPos(window, static_cast<int>(WIDTH / 2), static_cast<int>(HEIGHT / 2));
}
