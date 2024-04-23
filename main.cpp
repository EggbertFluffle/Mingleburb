#include <GLFW/glfw3.h>

#include "App.hpp"

App app;

int main() {
	app.init();
	app.run();

	return 0;
}

namespace Global {
	void propogateKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		app.player.propogateKeyCallback(window, &key, &scancode, &action, &mods);
	}

	void propogateMouseCallback(GLFWwindow* window, int button, int action, int mods) {
		app.player.propogateMouseCallback(window, &button, &action, &mods);
	}
}
