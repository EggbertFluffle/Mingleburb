#include <cstdint>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <stdexcept>
#include <iostream>

#include "Globals.hpp"
#include "GraphicsManager.hpp"
#include "Config.hpp"
#include "Block.hpp"
#include "stb_image.hpp"

#define IM_GUI_VEC(name, vec) ImGui::Text("%s: (%.3f, %.3f, %.3f)", name, vec.x, vec.y, vec.z)

GraphicsManager::GraphicsManager() : renderDistance(SQUARE_RENDER_DISTANCE) {
	initGLFW();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize GLAD\n");
	} 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	initBlockFaces();
	initUIElements();

	projection = glm::perspective(glm::radians(75.0f), (float)WIDTH/(float)HEIGHT, 0.1f, 100.0f);

	#ifdef DEBUG 
	initImGui();
	#endif
}

GraphicsManager::~GraphicsManager() {
	glfwTerminate();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}


uint GraphicsManager::loadTexture(const std::string path, const bool transparent) const {
	int texWidth, texHeight, nrChannels;
	stbi_uc* textureData = stbi_load(path.c_str(), &texWidth, &texHeight, &nrChannels, 0);

	uint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int colorFormat = transparent ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, colorFormat, texWidth, texHeight, 0, colorFormat, GL_UNSIGNED_BYTE, textureData);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Texture options get set for each axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Texture filtering modes are set per operation (minifying, magnifying);
	// Additionally defines which mipmap to use, mipmaps only matter when DOWNSCALING
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	stbi_image_free(textureData);

	return texture;
}

void GraphicsManager::loadBlockTexture(const uint id, const std::string path) {
	try {
		Blocks.at(id).textureID = loadTexture(path, false);
	} catch(std::out_of_range& err) {}
}

void GraphicsManager::loadUITexture(const uint id, const std::string path) {
	try {
		UIElements.at(id).textureID = loadTexture(path, true);
	} catch(std::out_of_range& err) {}
}

void GraphicsManager::initBlockFaces() {
	// Load a vertex array object for each block face
	for(int i = 0; i < 6; i++) {
		glGenVertexArrays(1, &blockFaceVAOs.at(i));

		glBindVertexArray(blockFaceVAOs.at(i));

		uint vbo;
		uint ebo;
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

	loadBlockTexture(BLOCKS::DIRT, "./assets/dirt.png");
	loadBlockTexture(BLOCKS::OAK_PLANKS, "./assets/oak_planks.png");
	loadBlockTexture(BLOCKS::PINK_WOOL, "./assets/pink_wool.png");

	blockShader.compileShaders("./shaders/blockVertex.glsl", "./shaders/blockFragment.glsl");

	blockShader.setMat4("projection", projection);
	blockShader.setInt("highlighted", false);
}

void GraphicsManager::initUIElements() {
	
	// Set the crosshair vertex array object
	// TODO: ZERO NEEDS TO BE REPLACED FOR MORE UI ELEMENTS
	glGenVertexArrays(1, &crosshairVAO);
	glBindVertexArray(crosshairVAO);

	uint vbo;
	uint ebo;
	glGenBuffers(1, &ebo);
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(UI_VERTICES), UI_VERTICES.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(RECT_INDICES), RECT_INDICES.data(), GL_STATIC_DRAW);

	// Vertex coordinates
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Texture coordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	loadUITexture(UI_ELEMENTS::CROSSHAIR, "./assets/crosshair.png");

	texturedUIShader.compileShaders("./shaders/UIVertex.glsl", "./shaders/UIFragment.glsl");
}

void GraphicsManager::initGLFW() {
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

void GraphicsManager::initImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(graphicsManager.window, true);
    ImGui_ImplOpenGL3_Init("#version 420");
}

void GraphicsManager::renderAllChunks() {
	blockShader.useShader();

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	blockShader.setMat4("view", view);
	blockShader.setMat4("projection", projection);


	// Chuks should only be loaded if they are within the render distance of the player
	for(auto& c : gameManager.chunks) {
		// c.loaded = std::pow(c.coords.x - (player.position.x - (float)CHUNK_WIDTH / 2) / CHUNK_WIDTH, 2) + 
		// 			 std::pow(c.coords.y - (player.position.z - (float)CHUNK_WIDTH / 2) / CHUNK_WIDTH, 2) <
		// 			 SQUARE_RENDER_DISTANCE;
		c.loaded = true;
	}

	// Render each face for all the blocks in a chunk
	for(int i = 0; i < 6; i++) {
		blockShader.setFloat("luminence", gameManager.faceLuminence[i]);
		for(auto& c : gameManager.chunks) {
			if(c.loaded) renderChunk(i, c);
		}
	}
}

void GraphicsManager::renderChunk(int& i, Chunk& c) {
	bindFace(i);
	// This char has one bit on corresponding to which cube face is being drawn
	// If the block doesn't have that face culled, the squad is send to draw
	uint8_t face = 0b00000100 << (6 - (i + 1));
	for(int z = 0; z < CHUNK_WIDTH; z++) {
		for(int y = 0; y < BUILD_HEIGHT; y++) {
			for(int x = 0; x < CHUNK_WIDTH; x++) {
				Block* curr = c.getBlock(x, y, z);
				// Current block is not air and should render the current face
				if(curr != nullptr && curr->id != 0 && curr->faces & face) {
					glm::mat4 model(1.0f);
					model = glm::scale(
						glm::translate(glm::mat4(1.0f), glm::vec3(
							0.5f + float(x) + (c.coords.x * CHUNK_WIDTH),
							0.5f + float(y),
							0.5f + float(z) + (c.coords.y * CHUNK_WIDTH)
						)),
						glm::vec3(0.5f, 0.5f, 0.5f)
					);
					blockShader.setMat4("model", model);
					blockShader.setInt("highlighted", curr->highlighted);

					bindTexture(Blocks.at(curr->id).textureID);

					glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
				}
				// Turn off highlighting for the highlighted block after its last face is drawn 
				if(i == 5 && curr->highlighted) curr->highlighted = false;
			}
		}
	}
}

void GraphicsManager::renderUI() {
	texturedUIShader.useShader();
	glBindVertexArray(crosshairVAO);
	// TODO: THIS SHADER SHOULD MAKE USE OF UIElementEntry PROPERTIES
	glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(0.03f, 0.03f, 1.0f));
	texturedUIShader.setMat4("model", model);
	bindTexture(UIElements.at(UI_ELEMENTS::CROSSHAIR).textureID);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
} 

void GraphicsManager::addDebugPoint(glm::vec3 vec) {
	debugPoints.emplace_back(vec);
}

void GraphicsManager::addDebugPoint(float x, float y, float z) {
	addDebugPoint(glm::vec3(x, y, z));
}

void GraphicsManager::renderDebugPoints() {
	ImGui::Begin("Debug Points");
	for(int i = 0; i < 6; i++) {
		for(glm::vec3& vec : debugPoints) {
			IM_GUI_VEC("debug", vec);
			bindFace(i);
			glm::mat4 model(1.0f);
			model = glm::scale(
				glm::translate(glm::mat4(1.0f), glm::vec3(
					vec.x,
					vec.y,
					vec.z
				)),
				glm::vec3(0.05f, 0.05f, 0.05f)
			);
			blockShader.setMat4("model", model);
			blockShader.setInt("highlighted", 0);

			bindTexture(Blocks.at(BLOCKS::DIRT).textureID);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}
	}
	ImGui::End();
	debugPoints.clear();
}

void GraphicsManager::bindTexture(const uint id) {
	if(lastBoundTextureID != id) {
		glBindTexture(GL_TEXTURE_2D, id);
		lastBoundTextureID = id;
	}
} 

void GraphicsManager::bindFace(const int face) {
	glBindVertexArray(blockFaceVAOs[face]);
}
