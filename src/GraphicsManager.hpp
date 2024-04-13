#pragma once

#include <glad/glad.h>
#include <map> 
#include <string> 

#include "stb_image.hpp"

class GraphicsManager {
	void loadBlockVertices();
	unsigned int blockFaceVAOs[6];
	std::map<std::string, unsigned int> textures;

public:
	GraphicsManager();
	void loadTexture(std::string, std::string path);
	void bindTexture(std::string name);
	void bindFace(int face);
};
