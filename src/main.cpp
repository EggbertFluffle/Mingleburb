#include <GLFW/glfw3.h>

#include "App.hpp"

int main() {
	App app;

	app.init();
	app.run();

	return 0;
}
