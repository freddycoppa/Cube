#pragma once

struct Shader {
	Shader(const char* vertexPath, const char* fragmentPath);
	void use() const;
	void setVec4(const char* name, int count, const float* value) const;
	void setFloat(const char* name, float value) const;
	void setVec3(const char* name, const float* value) const;
	void setMat4(const char* name, int count, const float* value) const;
	void setInt(const char* name, int value) const;
	~Shader();

private: unsigned program;
};
