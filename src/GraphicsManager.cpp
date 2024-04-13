
#include <glad/glad.h>
#include <string>

#include "GraphicsManager.hpp"
#include "Block.hpp"
#include "stb_image.hpp"

GraphicsManager::GraphicsManager() {
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

	printf("%s is equal to %d\n", name.c_str(), textures[name]);

	stbi_image_free(textureData);
}

void GraphicsManager::bindTexture(std::string name) {
	glBindTexture(GL_TEXTURE_2D, textures[name]);
} 

void GraphicsManager::bindFace(int face) {
	glBindVertexArray(blockFaceVAOs[face]);
}
