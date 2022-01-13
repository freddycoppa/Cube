#include <GL/glew.h>

#include "Shader.h"

#include <fstream>
#include <sstream>
#include <string>
#include <exception>
#include <iostream>

extern const char* vsSource;
extern const char* fsSource;

Shader::Shader(const char* vsPath, const char* fsPath) {
	/*std::stringstream vsCode;
	std::stringstream fsCode;
	std::ifstream vsFile;
	std::ifstream fsFile;
	vsFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fsFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	vsFile.open(vsPath);
	vsCode << vsFile.rdbuf();
	vsFile.close();
	fsFile.open(fsPath);
	fsCode << fsFile.rdbuf();
	fsFile.close();
	std::string vsString = vsCode.str(), fsString = fsCode.str();
	const char* vsSource = vsString.c_str(), * fsSource = fsString.c_str();*/
	GLuint vs, fs;
	GLint success;
	char infoLog[512];
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vsSource, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vs, 512, NULL, infoLog);
		std::cout << infoLog;
		throw std::exception(infoLog);
	}
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fsSource, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fs, 512, NULL, infoLog);
		throw std::exception(infoLog);
	}
	this->program = glCreateProgram();
	glAttachShader(this->program, vs);
	glAttachShader(this->program, fs);
	glLinkProgram(this->program);
	glGetProgramiv(this->program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->program, 512, NULL, infoLog);
		throw std::exception(infoLog);
	}
	glDetachShader(this->program, vs);
	glDetachShader(this->program, fs);
	glDeleteShader(vs);
	glDeleteShader(fs);
}

void Shader::use() const {
	glUseProgram(this->program);
}

void Shader::setVec4(const char* name, int count, const float* value) const {
	glUniform4fv(glGetUniformLocation(this->program, name), count, value);
}

void Shader::setFloat(const char* name, float value) const {
	glUniform1f(glGetUniformLocation(this->program, name), value);
}

void Shader::setVec3(const char* name, const float* value) const {
	glUniform3f(glGetUniformLocation(this->program, name), value[0], value[1], value[2]);
}

void Shader::setMat4(const char* name, int count, const float* value) const {
	glUniformMatrix4fv(glGetUniformLocation(this->program, name), count, GL_FALSE, value);
}

void Shader::setInt(const char* name, int value) const {
	glUniform1i(glGetUniformLocation(this->program, name), value);
}

Shader::~Shader() {
	glUseProgram(0);
	glDeleteProgram(this->program);
}
