#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>
#include <fstream> 
#include <sstream>
#include <string>

#include "./Shader.hpp"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
	id = compileShaders(vertexShaderPath, fragmentShaderPath);
}

void Shader::useShader() {
	glUseProgram(id);
}

void Shader::setInt(const char* name, int value) {
	glUniform1i(glGetUniformLocation(id, name), value);
}

void Shader::setFloat(const char* name, float value) {
	glUniform1f(glGetUniformLocation(id, name), value);
}

void Shader::setVec2(const char* name, float xValue, float yValue) {
	glUniform2f(glGetUniformLocation(id, name), xValue, yValue);
}

void Shader::setVec3(const char* name, float xValue, float yValue, float zValue) {
	glUniform3f(glGetUniformLocation(id, name), xValue, yValue, zValue);
}

void Shader::setMat4(const char* name, glm::mat4 &mat) {
	glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, glm::value_ptr(mat));
}

std::string Shader::loadShaderSource(const char* path) {
	std::ifstream input(path);
	if(!input.is_open()) {
		printf("Couldnt open shader file \"%s\"", path);
		return NULL;
	}
	
	std::stringstream ss;
	ss << input.rdbuf();
	input.close();

	return ss.str();
}

unsigned int Shader::compileShaders(const char* vertexShaderPath, const char* fragmentShaderPath) {
	// Create a shader and assign its id to vertexShader 
	unsigned int vertexShader;
	// Make the shader of type GL_VERTEX_SHADER 
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Copy the shader source code into it's OpenGL object memory
	// the second argument is the number of source code strings we are passing
	// TODO: COULD PROBABLY BE SOLVED WITH HEAP MEMORY MANAGEMENT
	std::string vertexShaderSource = loadShaderSource(vertexShaderPath);
	const char* vertexShaderSourcePointer = vertexShaderSource.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderSourcePointer, NULL);

	int shaderStatus;
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &shaderStatus);
	if(!shaderStatus) {
		char compilationLog[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, compilationLog);
		printf("Vertex shader compilation failed with the provided error:\n %s", compilationLog);
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// TODO: COULD PROBABLY BE SOLVED WITH HEAP MEMORY MANAGEMENT
	std::string fragmentShaderSource = loadShaderSource(fragmentShaderPath);
	const char* fragmentShaderSourcePointer = fragmentShaderSource.c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderSourcePointer, NULL);

	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &shaderStatus);
	if(!shaderStatus) {
		char compilationLog[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, compilationLog);
		printf("Fragment shader compilation failed with the provided error:\n %s", compilationLog);
	}

	// Combine the shaders into a shaderProgram object and add both shaders
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &shaderStatus);
	if(!shaderStatus) {
		char linkingLog[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, linkingLog);
		printf("Shader program linking error:\n %s", linkingLog);
	}

	// Free the vertex and fragment shaders from memory
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}
