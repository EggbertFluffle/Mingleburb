#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include "Globals.hpp"
#include "App.hpp"

void App::init() {
	graphicsManager.blockShader.useShader();
}

void App::run() {
	while(!glfwWindowShouldClose(graphicsManager.window)) {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		ImGui::NewFrame();
		ImGui::Begin("Debug");

		glfwPollEvents();

		deltaTime = glfwGetTime() - previousTime;
		previousTime = glfwGetTime();

		player.update(deltaTime);

		player.getLookAt(graphicsManager.view);

		graphicsManager.renderAllChunks();
		graphicsManager.renderDebugPoints();
		graphicsManager.renderUI();

		ImGui::End();
		ImGui::Render();

		#ifdef DEBUG
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		#endif

		glfwSwapBuffers(graphicsManager.window);

	}
}
