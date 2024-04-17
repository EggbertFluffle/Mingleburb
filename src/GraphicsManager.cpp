#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include "Globals.hpp"
#include "GraphicsManager.hpp"
#include "Block.hpp"
#include "stb_image.hpp"

GraphicsManager::GraphicsManager() {
	initializeGLFW();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize GLAD\n");
	} 

	glEnable(GL_DEPTH_TEST);

	for(char i = 0; i < 6; i++) {
		glGenVertexArrays(1, &blockFaceVAOs[i]);

		glBindVertexArray(blockFaceVAOs[i]);

		unsigned int vbo;
		unsigned int ebo;
		glGenBuffers(1, &ebo);
		glGenBuffers(1, &vbo);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(RECT_VERTICES[i]), RECT_VERTICES[i], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(RECT_INDICES), RECT_INDICES, GL_STATIC_DRAW);

		// Vertex coordinates
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// Texture coordinates
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	loadTexture("dirt", "./src/assets/dirt.png");
	loadTexture("pink_wool", "./src/assets/pink_wool.png");
	loadTexture("oak_planks", "./src/assets/oak_planks.png");

	shader.compileShaders("./src/shaders/vertex.glsl", "./src/shaders/fragment.glsl");

	projection = glm::perspective(glm::radians(75.0f), (float)WIDTH/(float)HEIGHT, 0.1f, 100.0f);

	shader.setMat4("projection", projection);

	shader.useShader();
}

GraphicsManager::~GraphicsManager() {
	glfwTerminate();
}

void GraphicsManager::loadTexture(std::string name, std::string path) {
	int texWidth, texHeight, nrChannels;
	unsigned char* textureData = stbi_load(path.c_str(), &texWidth, &texHeight, &nrChannels, 0);

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Texture options get set for each axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Texture filtering modes are set per operation (minifying, magnifying)
	// Additionally defines which mipmap to use, mipmaps only matter when DOWNSCALING
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	textures[name] = texture;

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

	glfwSetFramebufferSizeCallback(window, windowResizeCallback);
	glfwSetKeyCallback(window, (GLFWkeyfun)Global::propogateKeyCallback);
}

void GraphicsManager::bindTexture(std::string name) {
	glBindTexture(GL_TEXTURE_2D, textures[name]);
} 

void GraphicsManager::bindFace(int face) {
	glBindVertexArray(blockFaceVAOs[face]);
}


