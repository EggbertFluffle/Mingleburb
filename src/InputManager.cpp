#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stdexcept>

#include <imgui/imgui.h>

#include "InputManager.hpp"
#include "Config.hpp"

void InputManager::updatePressed() {
	if(mouseButton1Pressed) {
		mouseButton1Pressed = false;
	}

	if(mouseButton2Pressed) {
		mouseButton2Pressed = false;
	}

	for(auto& kp : keyPresses) {
		kp.second = false;
	}
}

bool InputManager::getKeyState(const int key) const {
	try {
		return keyStates.at(key);
	} catch(std::out_of_range& err) {
		return false;
	}
}

bool InputManager::getKeyPressed(const int key) {
	try {
		if(keyPresses.at(key)) {
			keyPresses.at(key) = false;
			return true;
		}
		return false;
	} catch(std::out_of_range& err) {
		return false;
	}
}

bool InputManager::getMouseButtonPressed(const int button) {
	switch(button) {
		case GLFW_MOUSE_BUTTON_1:
			if(mouseButton1Pressed) {
				mouseButton1Pressed = false;
				return true;
			}
			return false;
			break;
		case GLFW_MOUSE_BUTTON_2:
			if(mouseButton2Pressed) {
				mouseButton2Pressed = false;
				return true;
			}
			return false;
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
	keyStates[*key] = *action;
	keyPresses[*key] = *action;
}

void InputManager::mouseCallback(int* button, int* action, int* mods) {
	switch(*button) {
		case GLFW_MOUSE_BUTTON_1:
			mouseButton1Down = *action;
			if(*action) mouseButton1Pressed = true;
			break;
		case GLFW_MOUSE_BUTTON_2:
			mouseButton2Down = *action;
			if(*action) mouseButton2Pressed = true;
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
