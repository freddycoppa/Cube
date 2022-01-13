#include <GL/glew.h>

#include "FullscreenQuad.h"

static float quad[6][2] = {
	{-1.f, -1.f}, {1.f, -1.f}, {1.f, 1.f},
	{-1.f, -1.f}, {1.f, 1.f}, {-1.f, 1.f}
};

FullscreenQuad::FullscreenQuad() {
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);
	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void FullscreenQuad::draw() {
	glDisable(GL_DEPTH_TEST);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(quad) / (2 * sizeof(float)));
	glBindVertexArray(0);
}

FullscreenQuad::~FullscreenQuad() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}
