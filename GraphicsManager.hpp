#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <map> 
#include <string> 

#include "stb_image.hpp"
#include "Shader.hpp"

class GraphicsManager {
	void loadBlockVertices();
	unsigned int blockFaceVAOs[6];
	std::map<std::string, unsigned int> textures;

	void loadTexture(std::string, std::string path);

public:
	GLFWwindow* window;
	Shader shader;
	glm::mat4 view, projection;

	GraphicsManager();
	~GraphicsManager();
	void initializeGLFW();

	void bindTexture(std::string name);
	void bindFace(int face);

	static void windowResizeCallback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}
};
