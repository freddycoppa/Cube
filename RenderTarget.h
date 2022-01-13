#pragma once

#include <glm.hpp>

class RenderTarget {
	unsigned framebuffer, rbo;
	unsigned renderedTextures[2]; // rendered colors = 0, rendered locations = 1
	unsigned width, height;
	float* data;

public:
	RenderTarget(int width, int height);
	void resize(int width, int height);
	void bind();
	void unbind();
	void texApply();
	unsigned getWidth(), getHeight();
	float get(glm::vec2 loc);
	float sample(glm::vec2 v);
	~RenderTarget();
};
