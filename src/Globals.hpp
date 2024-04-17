#pragma once

// #define FULLSCREEN

#ifndef FULLSCREEN
const int WIDTH = 800;
const int HEIGHT = 600;
#else
const int WIDTH = 1920;
const int HEIGHT = 1080;
#endif

const int CHUNK_WIDTH = 16;
const int BUILD_HEIGHT = 32;

#define ENABLE_MOUSE_CONTROLS

#ifndef ENABLE_MOUSE_CONTROLS
const bool MOUSE_CONTROLS = false;
#else
const bool MOUSE_CONTROLS = true;
#endif

#define PI 3.14159

#include <GLFW/glfw3.h>

namespace Global {
	void propogateKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void propogateMouseCallback(GLFWwindow* window, int button, int action, int mods);
}
