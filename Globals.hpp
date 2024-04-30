#pragma once

#define FULLSCREEN
// #define ENABLE_MOUSE_CONTROLS

#ifndef FULLSCREEN
const int WIDTH = 800;
const int HEIGHT = 600;
#else
const int WIDTH = 1920;
const int HEIGHT = 1080;
#endif

const int CHUNK_WIDTH = 2;
const int BUILD_HEIGHT = 2;

#ifndef ENABLE_MOUSE_CONTROLS
const bool MOUSE_CONTROLS = false;
#else
const bool MOUSE_CONTROLS = true;
#endif

const int NOISE_FREQUENCY = 2;
const int NOISE_OCTAVES = 2;

#define PI 3.14159

#include <GLFW/glfw3.h>

namespace Global {
	void propogateKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void propogateMouseCallback(GLFWwindow* window, int button, int action, int mods);
}