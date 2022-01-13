#include <GL/glew.h>
#include <exception>
#include <iostream>
#include "Renderer.h"
#include <gtc/type_ptr.hpp>
#include "Shader.h"
#include "Texture.h"
#include "Cube.h"
#include <random>
#include <chrono>
#include "Logic.h"
#include <thread>
#include "Mouse.h"
#include "Events.h"
#include "ThreadSafeQueue.h"
#include "Application.h"
#include "RenderTarget.h"
#include "FullscreenQuad.h"

using namespace std;
using namespace glm;
using namespace Application;

static ThreadSafeQueue moves;
static Cube cube;
static Logic logic(moves, cube, frameTime, 46.f);

extern Texture genTexture(int width, int height, float radius, float power);

static void jumble();
static void solve();

int main() {
	try {
		//RenderTarget target(window.width, window.height);
		Renderer renderer(cube.data());

		//FRAMEBUFFERS AND ALL NEED TO BE DELETED AFTER GAME LOOP ENDS

		//FullscreenQuad quad;

		//int renderedColors = 0, renderedLocations = 1;
		/*GLuint framebuffer, renderedTextures[2]; // rendered colors = 0, rendered locations = 1;
		glGenFramebuffers(1, &framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glGenTextures(2, renderedTextures);
		glBindTexture(GL_TEXTURE_2D, renderedTextures[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, window.width, window.height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, renderedTextures[1]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, window.width, window.height, 0, GL_RGB, GL_FLOAT, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTextures[0], 0);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, renderedTextures[1], 0);
		unsigned int rbo;
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, window.width, window.height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
		GLenum drawBuffers[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
		glDrawBuffers(2, drawBuffers); 
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) throw std::exception("Couldn't create framebuffer!");*/

		//RenderTarget target(window.width, window.height);

		int width = 512, height = 512;
		float radius = 240.f;
		float power = 4.f;
		Texture texture = genTexture(width, height, radius, power);

		Shader shader("C:\\dev\\c++\\cube\\shaders\\vertex_shader.txt", "C:\\dev\\c++\\cube\\shaders\\fragment_shader.txt");
		shader.use();
		shader.setVec3("translation", value_ptr(vec3(0.f, 0.f, -7.5f)));
		shader.setInt("sampler", 0);

		/*Shader painter("C:\\dev\\c++\\cube\\shaders\\fullscreen_quad_vs.txt", "C:\\dev\\c++\\cube\\shaders\\fullscreen_quad_fs.txt");
		painter.use();
		painter.setInt("sampler", 0);*/

		mat4 rotation(1);

		std::thread jumbler(jumble);

		while (!shouldClose()) {
			/*if (resized) {
				target.resize(window.width, window.height);
				resized = false;
			}*/

			if (events.leftClick) {
				vec3 axis = vec3(-mouse.velocity.y, mouse.velocity.x, 0); // needs to be normalized with frame rate ???
				if (axis != vec3(0, 0, 0)) {
					mat4 m(1);
					m = rotate(m, 2 * length(mouse.velocity), axis);
					rotation = m * rotation;
				}
			}

			logic.update();

			if (events.turn and not logic.turning) moves.push({ events.side, events.direction });

			/*if (*//*iters != 0*//*events.k and not turning) {
				turning = true;
				Cube::Side s = static_cast<Cube::Side>(generator() % 6);
				while (s == side) s = static_cast<Cube::Side>(generator() % 6);
				side = s;
				direction = static_cast<bool>(generator() % 2);
				if (side == Cube::RED or side == Cube::YELLOW or side == Cube::BLUE) da = -0.125f;
				else da = +0.125f;
				da *= directions[direction];
				//iters--;
			}*/

			if (events.reset) cube.reset();

			shader.use();
			if (!events.minimized)
			shader.setMat4("projection", 1, value_ptr(perspective(pi<float>() / 4, window.aspectRatio(), 1.f, 10.f)));
			shader.setMat4("rotation", 1, value_ptr(rotation));
			shader.setVec3("sideToBeRotated", logic.sideToBeRotatedPtr());
			shader.setMat4("sideRotation", 1, logic.sideRotationPtr());

			texture.apply();

			//target.bind();

			renderer.draw();

			/*target.unbind();
			painter.use();
			target.texApply();
			quad.draw();*/

			//std::cout << target.get(mouse.pos) << std::endl;

			update();
		}

		jumbler.join();
	} 
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
}

void jumble() {
	std::mt19937 generator((unsigned)std::chrono::high_resolution_clock::now().time_since_epoch().count());
	Cube::Side previousSide = static_cast<Cube::Side>(generator() % 6);
	while (!shouldClose()) {
		if (events.jumble and not logic.turning) {
			Cube::Side s = static_cast<Cube::Side>(generator() % 6);
			while (s == previousSide) s = static_cast<Cube::Side>(generator() % 6);
			previousSide = s;
			moves.push({ s, static_cast<bool>(generator() % 2) });
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void solve() {
	while (not window.shouldClose()) {
		if (events.solve) {
			// block all turn events
			events.blocked = true;

			// green cross

			i32vec3 edgeLocations[4];
			int index = 0;
			for (int j = 0; j < 3; j++) for (int k = 0; k < 3; k++) for (int c = 0; c < 6; c++) 
				if (cube.cubies[1][j][k][c] == Cube::GREEN) {
					
				}
			for (int k = 0; k < 3; k++) for (int i = 0; i < 3; i++) for (int c = 0; c < 6; c++) 
				if (cube.cubies[i][1][k][c] == Cube::GREEN) {
					edgeLocations[index] = { i, 1, k };
					index++;
				}
			for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) for (int c = 0; c < 6; c++) 
				if (cube.cubies[i][j][1][c] == Cube::GREEN) {
					edgeLocations[index] = { i, j, 1 };
					index++;
				}

			for (int i = 0; i < 4; i++) {

			}

			// unblock all turn events
			events.blocked = false;

			events.solve = false;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}