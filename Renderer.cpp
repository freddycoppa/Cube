#include <GL/glew.h>

#include "Renderer.h"

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <vector>

using namespace std;
using namespace glm;

static constexpr float quadMesh[6][5] = {
	{-0.5f, -0.5f, -0.5f, 0.f, 0.f}, {-0.5f, 0.5f, -0.5f, 0.f, 1.f}, {0.5f, 0.5f, -0.5f, 1.f, 1.f}, 
	{-0.5f, -0.5f, -0.5f, 0.f, 0.f}, {0.5f, 0.5f, -0.5f, 1.f, 1.f}, {0.5f, -0.5f, -0.5f, 1.f, 0.f}
};

struct Vertex {
	vec3 position;
	vec2 uv;
};

vector<Vertex> roundedQuadMesh;

float root2 = sqrtf(2.f);

static float radius(float theta, float a) {
	return (root2 * a) / powf(3.f + cosf(4.f * theta), 0.25f);
}

static float x(float r, float theta) {
	return r * cosf(theta);
}

static float y(float r, float theta) {
	return r * sinf(theta);
}

static void recursiveMesh(float first, float last, float a, vector<Vertex>& mesh, unsigned res) {
	if (res == 0) return;
	float r = radius(first, a);
	mesh.push_back({ {x(r, first), y(r, first), -a}, {0, 0} });
	float middle = (first + last) / 2;
	r = radius(middle, a);
	mesh.push_back({ {x(r, middle), y(r, middle), -a}, {0, 0} });
	r = radius(last, a);
	mesh.push_back({ {x(r, last), y(r, last), -a}, {0, 0} });
	recursiveMesh(first, middle, a, mesh, res - 1);
	recursiveMesh(middle, last, a, mesh, res - 1);
}

static vector<Vertex> generateMesh(float a, unsigned res) {
	vector<Vertex> mesh;
	float theta = 5 * pi<float>() / 4;
	float r = radius(theta, a);
	mesh.push_back({ {x(r, theta), y(r, theta), -a}, {0, 0} });
	theta = 3 * pi<float>() / 4;
	r = radius(theta, a);
	mesh.push_back({ {x(r, theta), y(r, theta), -a}, {0, 0} });
	theta = pi<float>() / 4;
	r = radius(theta, a);
	mesh.push_back({ {x(r, theta), y(r, theta), -a}, {0, 0} });
	theta = 5 * pi<float>() / 4;
	r = radius(theta, a);
	mesh.push_back({ {x(r, theta), y(r, theta), -a}, {0, 0} });
	theta = pi<float>() / 4;
	r = radius(theta, a);
	mesh.push_back({ {x(r, theta), y(r, theta), -a}, {0, 0} });
	theta = 7 * pi<float>() / 4;
	r = radius(theta, a);
	mesh.push_back({ {x(r, theta), y(r, theta), -a}, {0, 0} });
	recursiveMesh(1 * pi<float>() / 4, -1 * pi<float>() / 4, a, mesh, res);
	recursiveMesh(7 * pi<float>() / 4, 5 * pi<float>() / 4, a, mesh, res);
	recursiveMesh(5 * pi<float>() / 4, 3 * pi<float>() / 4, a, mesh, res);
	recursiveMesh(3 * pi<float>() / 4, 1 * pi<float>() / 4, a, mesh, res);
	return mesh;
}

static vector<Vertex> generateMesh1() {
	vector<Vertex> mesh;
	mesh.push_back({ { -0.5f, -0.5f, -0.5f }, {0.f, 0.f} });
	mesh.push_back({ { -0.5f, 0.5f, -0.5f }, {0.f, 1.f} });
	mesh.push_back({ { 0.5f, 0.5f, -0.5f }, {1.f, 1.f} });
	mesh.push_back({ { -0.5f, -0.5f, -0.5f }, {0.f, 0.f} });
	mesh.push_back({ { 0.5f, 0.5f, -0.5f }, {1.f, 1.f} });
	mesh.push_back({ { 0.5f, -0.5f, -0.5f }, {1.f, 0.f} });
	return mesh;
}


Renderer::Renderer(void* colors) : buffer(false), colors(colors) {
	/*for (float x = -0.5f; x < 0.5f; x += 0.001f) for (float y = -0.5; y < 0.5f; y += 0.001f) {
		if ((powf(x, 4.f) + powf(y, 4.f)) <= 0.5f) {
			Vertex v;
			v.position.x = x;
			v.position.y = y;
			v.position.z = -0.5f;
			v.uv.x = x + 0.5f;
			v.uv.y = y + 0.5f;
			roundedQuadMesh.push_back(v);
		}
	}*/

	//roundedQuadMesh = generateMesh(0.5f, 5);
	roundedQuadMesh = generateMesh1();

	glGenBuffers(1, &this->quadInstance);
	glBindBuffer(GL_ARRAY_BUFFER, this->quadInstance);
	glBufferData(GL_ARRAY_BUFFER, /*sizeof(quadMesh)*/ roundedQuadMesh.size() * sizeof(Vertex), /*quadMesh*/ & roundedQuadMesh[0], GL_STATIC_DRAW);
	glGenBuffers(1, &this->positions);
	glBindBuffer(GL_ARRAY_BUFFER, this->positions);
	glBufferData(GL_ARRAY_BUFFER, 6 * 3 * 3 * sizeof(vec3), nullptr, GL_STATIC_DRAW);
	glGenBuffers(1, &this->axes);
	glBindBuffer(GL_ARRAY_BUFFER, this->axes);
	glBufferData(GL_ARRAY_BUFFER, 6 * 3 * 3 * sizeof(vec3), nullptr, GL_STATIC_DRAW);
	glGenBuffers(1, &this->sines);
	glBindBuffer(GL_ARRAY_BUFFER, this->sines);
	glBufferData(GL_ARRAY_BUFFER, 6 * 3 * 3 * sizeof(float), nullptr, GL_STATIC_DRAW);
	glGenBuffers(1, &this->cosines);
	glBindBuffer(GL_ARRAY_BUFFER, this->cosines);
	glBufferData(GL_ARRAY_BUFFER, 6 * 3 * 3 * sizeof(float), nullptr, GL_STATIC_DRAW);
	glGenBuffers(1, &this->locations);
	glBindBuffer(GL_ARRAY_BUFFER, this->locations);
	glBufferData(GL_ARRAY_BUFFER, 6 * 3 * 3 * sizeof(vec3), nullptr, GL_STATIC_DRAW);
	this->setData(Cube::FRONT, vec3(-1, 0, 0), 0, -1); // front face
	this->setData(Cube::UP, vec3(1, 0, 0), 1, 0); // up face
	this->setData(Cube::LEFT, vec3(0, 1, 0), 1, 0); // left face
	this->setData(Cube::BACK, vec3(1, 0, 0), 0, 1); // back face
	this->setData(Cube::DOWN, vec3(-1, 0, 0), 1, 0); // down face
	this->setData(Cube::RIGHT, vec3(0, -1, 0), 1, 0); // right face
	glGenVertexArrays(2, this->vaos);
	glGenBuffers(2, this->vbos);
	for (int i = 0; i < 2; i++) {
		GLuint vao = this->vaos[i];
		GLuint vbo = this->vbos[i];
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, this->quadInstance);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec2) + sizeof(vec3), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vec2) + sizeof(vec3), (void*)sizeof(vec3));
		glBindBuffer(GL_ARRAY_BUFFER, this->positions);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);
		glVertexAttribDivisor(2, 1);
		glBindBuffer(GL_ARRAY_BUFFER, this->axes);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);
		glVertexAttribDivisor(3, 1);
		glBindBuffer(GL_ARRAY_BUFFER, this->sines);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
		glVertexAttribDivisor(4, 1);
		glBindBuffer(GL_ARRAY_BUFFER, this->cosines);
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
		glVertexAttribDivisor(5, 1);
		glBindBuffer(GL_ARRAY_BUFFER, this->locations);
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribDivisor(6, 1);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, 6 * 9 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(7);
		glVertexAttribPointer(7, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
		glVertexAttribDivisor(7, 1);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer::draw() {
	GLuint vao = this->vaos[this->buffer];
	this->buffer = !this->buffer;
	GLuint vbo = this->vbos[this->buffer];
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 6 * 9 * sizeof(float), this->colors);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(vao);
	glDrawArraysInstanced(GL_TRIANGLES, 0, /*sizeof(quadMesh) / (sizeof(vec2) + sizeof(vec3))*/ roundedQuadMesh.size(), 6 * 9);
	// CHECK ABOVE IF ANYTHING GOES WRONG; THE THIRD PARAMETER
	glBindVertexArray(0);
}

void Renderer::setData(Cube::Side side, vec3 axis, float sine, float cosine) {
	static int offset = 0;
	vec3 pos = Cube::facePositions[side];
	int xoff = int(abs(pos.x));
	int yoff = int(abs(pos.y));
	int zoff = int(abs(pos.z));
	for (int x = xoff - 1; x < 2 - xoff; x++)
		for (int y = yoff - 1; y < 2 - yoff; y++)
			for (int z = zoff - 1; z < 2 - zoff; z++) {
				vec3 v = pos + vec3(x, y, z);
				glBindBuffer(GL_ARRAY_BUFFER, this->positions);
				glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(vec3), sizeof(v), value_ptr(v));
				glBindBuffer(GL_ARRAY_BUFFER, this->axes);
				glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(vec3), sizeof(axis), value_ptr(axis));
				glBindBuffer(GL_ARRAY_BUFFER, this->sines);
				glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(float), sizeof(sine), &sine);
				glBindBuffer(GL_ARRAY_BUFFER, this->cosines);
				glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(float), sizeof(cosine), &cosine);
				glBindBuffer(GL_ARRAY_BUFFER, this->locations);
				vec3 loc;
				if (xoff != 0) loc = { side, y, z };
				else if (yoff != 0) loc = { side, x, z };
				else if (zoff != 0) loc = { side, x, y };
				glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(vec3), sizeof(loc), value_ptr(loc));
				offset++;
			}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Renderer::~Renderer() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	for (int i = 0; i < 8; i++) glDisableVertexAttribArray(i);
	glDeleteBuffers(2, this->vbos);
	glDeleteBuffers(1, &this->positions);
	glDeleteBuffers(1, &this->axes);
	glDeleteBuffers(1, &this->sines);
	glDeleteBuffers(1, &this->cosines);
	glDeleteBuffers(1, &this->quadInstance);
	glDeleteBuffers(1, &this->locations);
	glDeleteVertexArrays(2, this->vaos);
}
