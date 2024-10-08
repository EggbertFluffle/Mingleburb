#pragma once

#include <vector> 

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "stb_image.hpp"
#include "Shader.hpp"
#include "Chunk.hpp"

class GraphicsManager {
	std::array<unsigned int, 6> blockFaceVAOs;
	int renderDistance;

	void loadTexture(const char* name, const char* path);
	void loadBlockVertices();

public:
	GLFWwindow* window;
	Shader shader;
	glm::mat4 view, projection;
	std::vector<unsigned int> BLOCK_ID_TO_TEXTURE_ID;

	GraphicsManager();
	~GraphicsManager();
	void initializeGLFW();

	void bindTexture(const int id);
	void bindFace(const int face);
	void renderAllChunks();
	void renderChunk(int& i, Chunk& c);

	static void windowResizeCallback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}
};
