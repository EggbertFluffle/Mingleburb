#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_projection.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
unsigned int id;

std::string loadShaderSource(const char* path);

public:
	void compileShaders(const char* vertexShaderPath, const char* fragmentShaderPath);
	void setBoolean(const char* name, bool value);
	void setInt(const char* name, int value);
	void setFloat(const char* name, float value);
	void setVec2(const char* name, float xValue, float yValue);
	void setVec3(const char* name, float xValue, float yValue, float zValue);
	void setMat4(const char* name, glm::mat4 &mat);
	void useShader();
};
