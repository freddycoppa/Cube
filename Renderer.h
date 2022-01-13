#pragma once

#include <glm.hpp>
#include "Cube.h"

class Renderer {
	unsigned vaos[2], vbos[2], positions, axes, sines, cosines, locations, quadInstance;
	bool buffer;
	void* colors;


	void setData(Cube::Side side, glm::vec3 axis, float sine, float cosine);
public:
	Renderer(void* colors);
	void draw();
	~Renderer();
};
