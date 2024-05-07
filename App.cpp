#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Globals.hpp"
#include "App.hpp"

App::App() :
	gameManager(),
	player((gameManager.worldWidth / 2) * CHUNK_WIDTH, 15, (gameManager.worldWidth / 2) * CHUNK_WIDTH, HALF_PI, 0.0f),
	graphicsManager()
{}

App::~App() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void App::init() {
	graphicsManager.shader.useShader();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui_ImplGlfw_InitForOpenGL(graphicsManager.window, true);
	ImGui_ImplOpenGL3_Init();
}

void App::run() {
	while(!glfwWindowShouldClose(graphicsManager.window)) {
		glfwPollEvents();

		if(player.inputManager.getKeyState(GLFW_KEY_Q)) {
			glfwSetWindowShouldClose(graphicsManager.window, true);
		}

		player.update(graphicsManager.window, &gameManager);

		player.getLookAt(graphicsManager.view);

		graphicsManager.renderAllChunks(&gameManager, &player);
		graphicsManager.renderDebug(&gameManager.debug);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Text("Hello world %f", player.yaw);

		// ImGui::DragFloat("yaw", &player.yaw, 0.0f, PI * 2.0f);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(graphicsManager.window);
	}
}
