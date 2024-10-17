#pragma once

#include <vector> 
#include <string>

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "stb_image.hpp"
#include "Shader.hpp"
#include "Chunk.hpp"

inline const std::array<int, 6> RECT_INDICES = {
	0, 1, 2,
	1, 2, 3
};

struct BlockReferance {
	uint blockID;
	bool breakable;
	float timeToBreak;

	uint textureID;

	BlockReferance(const uint _blockID, const bool _breakable, const float _timeToBreak) :
		blockID(_blockID),
		breakable(_breakable),
		timeToBreak(_timeToBreak) {}
};

namespace BLOCKS {
	enum BlockID {
		AIR,
		DIRT,
		OAK_PLANKS,
		PINK_WOOL,
		BLOCK_COUNT
	};
}

inline std::array<BlockReferance, BLOCKS::BLOCK_COUNT> Blocks = {
	BlockReferance(
		BLOCKS::AIR,
		false,
		0.0f
	),
	BlockReferance(
		BLOCKS::DIRT,
		true,
		0.5f
	),
	BlockReferance(
		BLOCKS::OAK_PLANKS,
		true,
		1.0f
	),
	BlockReferance(
		BLOCKS::PINK_WOOL,
		true,
		10.0f
	)
};

struct UIElementEntry {
	uint uiElementID;
	glm::vec2 position;
	glm::vec2 dimensions;

	uint textureID;

	UIElementEntry(const uint _uiElementID, const float _u, const float _v, const float _width, const float _height) :
		uiElementID(_uiElementID),
		position(_u, _v),
		dimensions(_width, _height) {};
};

namespace UI_ELEMENTS {
	enum UIElementID {
		CROSSHAIR,
		UI_ELEMENT_COUNT
	};
}

inline std::array<UIElementEntry, UI_ELEMENTS::UI_ELEMENT_COUNT> UIElements = {
	UIElementEntry(
		UI_ELEMENTS::CROSSHAIR,
		0.5, 1,
		25, 25
	)
};

inline const std::array<float, 16> UI_VERTICES = {
	-1.0f, 1.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f, 1.0f,
	1.0f, -1.0f, 1.0f, 1.0f
};

class GraphicsManager {
	std::array<uint, 6> blockFaceVAOs;
	int renderDistance;
	uint lastBoundTextureID = -1;

	uint loadTexture(const std::string path, const bool transparent) const;
	uint loadVertices();

	void loadBlockTexture(const uint id, const std::string path);
	void loadUITexture(const uint id, const std::string path);

public:
	GLFWwindow* window;
	float resolution;
	
	Shader texturedUIShader;
	uint crosshairVAO;

	Shader blockShader;
	glm::mat4 view, projection;
	std::vector<glm::vec3> debugPoints;

	GraphicsManager();
	~GraphicsManager();
	void initGLFW();
	void initImGui();
	void initBlockFaces();
	void initUIElements();

	void bindTexture(const uint id);
	void bindFace(const int face);
	void renderAllChunks();
	void renderChunk(int& i, Chunk& c);
	void renderUI();

	void addDebugPoint(float x, float y, float z);
	void addDebugPoint(glm::vec3 vec);
	void renderDebugPoints();
};
