#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>
#include <fstream> 
#include <sstream>
#include <string>

#include "./Shader.hpp"

void Shader::useShader() {
	glUseProgram(id);
}

void Shader::setBoolean(const char* name, bool value) {
	glUniform1i(glGetUniformLocation(id, name), value);
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

std::string Shader::loadShaderSource(const char* path, int& shaderStatus) {
	std::ifstream input(path);
	if(!input.is_open()) {
		printf("Couldnt open shader file \"%s\"", path);
		shaderStatus = -1;
		return "ERROR";
	}

	std::stringstream ss;
	ss << input.rdbuf();
	input.close();

	return ss.str();
}

void Shader::compileShaders(const char* vertexShaderPath, const char* fragmentShaderPath) {
	int shaderStatus;

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	std::string vertexShaderSource = loadShaderSource(vertexShaderPath, shaderStatus);
	if(shaderStatus == -1) {
		printf("ERROR: cannot find shader file at path: \"%s\"\n", vertexShaderPath);
	}

	const char* vertexShaderSourcePointer = vertexShaderSource.c_str();

	glShaderSource(vertexShader, 1, &vertexShaderSourcePointer, NULL);

	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &shaderStatus);
	if(!shaderStatus) {
		char compilationLog[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, compilationLog);
		printf("Vertex shader compilation failed with the provided error:\n %s", compilationLog);
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	std::string fragmentShaderSource = loadShaderSource(fragmentShaderPath, shaderStatus);
	if(shaderStatus == -1) {
		printf("ERROR: cannot find shader file at path: \"%s\"\n", fragmentShaderPath);
	}
	const char* fragmentShaderSourcePointer = fragmentShaderSource.c_str();

	glShaderSource(fragmentShader, 1, &fragmentShaderSourcePointer, NULL);
 
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &shaderStatus);
	if(!shaderStatus) {
		char compilationLog[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, compilationLog);
		printf("Fragment shader compilation failed with the provided error:\n %s", compilationLog);
	}

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

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	id = shaderProgram;
}
