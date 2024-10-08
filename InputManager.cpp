#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stdexcept>

#include "InputManager.hpp"
#include "Config.hpp"

void InputManager::setKeyTrue(const int key) {
	keyStates[key] = true;
}

void InputManager::setKeyFalse(const int key) {
	keyStates[key] = false;
}

bool InputManager::getKeyState(const int key) const {
	try {
		return keyStates.at(key);
	} catch(std::out_of_range err) {
		return false;
	}
}

bool InputManager::getMouseButtonPressed(const int button) {
	switch(button) {
		case GLFW_MOUSE_BUTTON_1:
			return mouseButton1Pressed;
			break;
		case GLFW_MOUSE_BUTTON_2:
			return mouseButton2Pressed;
			break;
		default: 
			return false;
			break;
	}
}

bool InputManager::getMouseButtonDown(const int button) const {
	switch(button) {
		case GLFW_MOUSE_BUTTON_1:
			return mouseButton1Down;
			break;
		case GLFW_MOUSE_BUTTON_2:
			return mouseButton2Down;
			break;
		default: 
			return false;
			break;
	}
}

void InputManager::keyCallback(int* key, int* scancode, int* action, int* mods) {
	if (*action) {
		setKeyTrue(*key);
	} else {
		setKeyFalse(*key);
	}
}

void InputManager::mouseCallback(int* button, int* action, int* mods) {
	switch(*button) {
		case GLFW_MOUSE_BUTTON_1:
			mouseButton1Down = *action;
			break;
		case GLFW_MOUSE_BUTTON_2:
			mouseButton2Down = *action;
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
