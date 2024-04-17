#pragma once

#define FULLSCREEN

#ifndef FULLSCREEN
const int WIDTH = 800;
const int HEIGHT = 600;
#else
const int WIDTH = 1920;
const int HEIGHT = 1080;
#endif

const int CHUNK_WIDTH = 8;
const int BUILD_HEIGHT = 8;

// #define MOUSE_CONTROLS

#ifndef MOUSE_CONTROLS
const bool MOUSE_CONTROLS = false;
#else
const bool MOUSE_CONTROLS = true;
#endif

#define WIDTH 800
#define HEIGHT 600

#define PI 3.14159

#include <GLFW/glfw3.h>

namespace Global {
	void propogateKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
}
