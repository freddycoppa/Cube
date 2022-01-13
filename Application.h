#pragma once

#include <GLFW/glfw3.h>
#include <glm.hpp>
#include "Cube.h"

namespace Application {
	extern class Window {
	public:
		int width, height;
		Window(int width, int height, const char* title);
		bool shouldClose();
		void update();
		float aspectRatio();
		~Window();
	private:
		GLFWwindow* window;
	} window;

	extern bool resized;

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
	void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	extern struct Mouse {
		glm::vec2 prevPos{ 0, 0 }, pos{ 0, 0 }, velocity{ 0, 0 };
		bool leftClick = false;
	} mouse;

	extern struct Events {
		bool
			leftClick = false,
			clicked = false,
			turn = false,
			blocked = false,
			direction = false,
			minimized = false,
			reset = false,
			jumble = false,
			solve = false;
		Cube::Side side;
	} events;

	bool shouldClose();
	void update();

	extern int fps;
	extern long long frameTime;
}
