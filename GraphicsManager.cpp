#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include "Globals.hpp"
#include "Config.hpp"
#include "Block.hpp"
#include "stb_image.hpp"

GraphicsManager::GraphicsManager() : renderDistance(SQUARE_RENDER_DISTANCE) {
	initializeGLFW();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize GLAD\n");
	} 

	glEnable(GL_DEPTH_TEST);

	for(int i = 0; i < 6; i++) {
		glGenVertexArrays(1, &blockFaceVAOs.at(i));

		glBindVertexArray(blockFaceVAOs.at(i));

		unsigned int vbo;
		unsigned int ebo;
		glGenBuffers(1, &ebo);
		glGenBuffers(1, &vbo);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(RECT_VERTICES.at(i)), RECT_VERTICES.at(i).data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(RECT_INDICES), RECT_INDICES.data(), GL_STATIC_DRAW);

		// Vertex coordinates
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// Texture coordinates
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	BLOCK_ID_TO_TEXTURE_ID.emplace_back(0);

	loadTexture("dirt", "./assets/dirt.png");
	loadTexture("pink_wool", "./assets/pink_wool.png");
	loadTexture("oak_planks", "./assets/oak_planks.png");

	shader.compileShaders("./shaders/vertex.glsl", "./shaders/fragment.glsl");

	projection = glm::perspective(glm::radians(75.0f), (float)WIDTH/(float)HEIGHT, 0.1f, 100.0f);

	shader.setMat4("projection", projection);
	shader.setInt("highlighted", false);
}

GraphicsManager::~GraphicsManager() {
	glfwTerminate();
}

void GraphicsManager::loadTexture(const char* name, const char* path) {
	int texWidth, texHeight, nrChannels;
	stbi_uc* textureData = stbi_load(path, &texWidth, &texHeight, &nrChannels, 0);

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Texture options get set for each axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Texture filtering modes are set per operation (minifying, magnifying);
	// Additionally defines which mipmap to use, mipmaps only matter when DOWNSCALING
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	BLOCK_ID_TO_TEXTURE_ID.push_back(texture);

	stbi_image_free(textureData);
}

void GraphicsManager::initializeGLFW() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Mingelburb", NULL, NULL);
	if (window == NULL) {
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	// Callback for whent the size of the window is modified
	glfwSetFramebufferSizeCallback(window, windowResizeCallback);
}

void GraphicsManager::renderAllChunks() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.setMat4("view", view);
	shader.setMat4("projection", projection);

	shader.useShader();

	// Chuks should only be loaded if they are within the render distance of the player
	for(auto& c : gameManager.chunks) {
		c.loaded = std::pow(c.coords.x - (player.position.x - (float)CHUNK_WIDTH / 2) / CHUNK_WIDTH, 2) + 
					 std::pow(c.coords.y - (player.position.z - (float)CHUNK_WIDTH / 2) / CHUNK_WIDTH, 2) <
					 SQUARE_RENDER_DISTANCE;
	}

	// Render each face for all the blocks in a chunk
	for(int i = 0; i < 6; i++) {
		shader.setFloat("luminence", gameManager.faceLuminence[i]);
		for(auto& c : gameManager.chunks) {
			if(c.loaded) renderChunk(i, c);
		}
	}
}

void GraphicsManager::renderChunk(int& i, Chunk& c) {
	bindFace(i);
	// This char has one bit on corresponding to which cube face is being drawn
	// If the block doesn't have that face culled, the squad is send to draw
	unsigned char face = 0b00000100 << (6 - (i + 1));
	for(int z = 0; z < CHUNK_WIDTH; z++) {
		for(int y = 0; y < BUILD_HEIGHT; y++) {
			for(int x = 0; x < CHUNK_WIDTH; x++) {
				Block* curr = c.getBlock(x, y, z);
				// Current block is not air and should render the current face
				if(curr != nullptr && curr->id != 0 && curr->faces & face) {
					glm::mat4 model(1.0f);
					model = glm::scale(
						glm::translate(glm::mat4(1.0f), glm::vec3(
							float(x) + (c.coords.x * CHUNK_WIDTH),
							float(y),
							float(z) + (c.coords.y * CHUNK_WIDTH)
						)),
						glm::vec3(0.5f, 0.5f, 0.5f)
					);
					shader.setMat4("model", model);
					shader.setInt("highlighted", curr->highlighted);

					bindTexture(BLOCK_ID_TO_TEXTURE_ID.at(curr->id + 1));

					glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

				}
				// Turn off highlighting for the highlighted block after its last face is drawn 
				if(i == 5 && curr->highlighted) curr->highlighted = false;
			}
		}
	}
}

void GraphicsManager::bindTexture(const int id) {
	glBindTexture(GL_TEXTURE_2D, id);
} 

void GraphicsManager::bindFace(const int face) {
	glBindVertexArray(blockFaceVAOs[face]);
}


