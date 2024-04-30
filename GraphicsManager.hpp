#pragma once

#include <vector> 

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <forward_list>

#include "GameManager.hpp"
#include "Chunk.hpp"
#include "stb_image.hpp"
#include "Shader.hpp"

class GraphicsManager {
	unsigned int blockFaceVAOs[6];

	void loadTexture(const char* name, const char* path);
	void loadBlockVertices();

public:
	GLFWwindow* window;
	Shader shader;
	glm::mat4 view, projection;
	Block* highlightedBlock;
	std::vector<unsigned int> BLOCK_ID_TO_TEXTURE_ID;

	GraphicsManager();
	~GraphicsManager();
	void initializeGLFW();

	void bindTexture(int id);
	void bindFace(int face);
	void renderAllChunks(GameManager* gameManager);
	void renderChunk(int& i, std::forward_list<Chunk>::iterator it);

	static void windowResizeCallback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}
};
