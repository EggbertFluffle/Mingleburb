#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <map> 
#include <string> 
#include <forward_list>

#include "Chunk.hpp"
#include "stb_image.hpp"
#include "Shader.hpp"

class GraphicsManager {
	void loadBlockVertices();
	unsigned int blockFaceVAOs[6];
	std::map<std::string, unsigned int> textures;

	void loadTexture(const char* name, const char* path);

public:
	GLFWwindow* window;
	Shader shader;
	glm::mat4 view, projection;

	GraphicsManager();
	~GraphicsManager();
	void initializeGLFW();

	void bindTexture(int* id);
	void bindFace(int face);
	void renderChunk(int& i, std::forward_list<Chunk>::iterator it);

	static void windowResizeCallback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}
};
