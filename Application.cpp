#include <GL/glew.h>
#include <exception>
#include <chrono>
#include <iostream>

#include "Application.h"
#include "RenderTarget.h"

namespace Application {
	Window::Window(int width, int height, const char* title) : width(width), height(height) {
		if (!glfwInit()) throw std::exception("Failed to initialize GLFW!");
		window = glfwCreateWindow(width, height, title, NULL, NULL);
		if (window == NULL) throw std::exception("Failed to create window!");
		//glfwSetCursorPos(window, width / 2., height / 2.);
		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetKeyCallback(window, keyCallback);
		glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
		glfwSetCursorPosCallback(window, cursorPosCallback);
		glfwSetMouseButtonCallback(window, mouseButtonCallback);
		//glfwWindowHint(GLFW_SAMPLES, 4);
		glfwMakeContextCurrent(window);
		if (glewInit() != GLEW_OK) throw std::exception("Failed to initialize OpenGL!"); 
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		//glEnable(GL_MULTISAMPLE);
	}

	bool Window::shouldClose() {
		return glfwWindowShouldClose(window);
	}

	void Window::update() {
		glfwSwapBuffers(window);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	float Window::aspectRatio() {
		//int w, h;
		//glfwGetFramebufferSize(window, &w, &h);
		//std::cout << w << ", " << width << std::endl;
		//std::cout << h << ", " << height << std::endl;
		return float(width) / float(height);
	}

	Window::~Window() {
		glfwTerminate();
	}

	Window window(1200, 675, "cube");

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (action == GLFW_PRESS) switch (key) {
		case GLFW_KEY_SPACE:
			events.reset = true; //and not events.blocked; 
			break;
		case GLFW_KEY_J:
			events.jumble = !events.jumble; break;
		case GLFW_KEY_S:
			events.solve = true; break;
		case GLFW_KEY_1:
			events.direction = false;
			events.turn = true and not events.blocked;
			events.side = Cube::FRONT; break;
		case GLFW_KEY_2:
			events.direction = false;
			events.turn = true and not events.blocked;
			events.side = Cube::UP; break;
		case GLFW_KEY_3:
			events.direction = false;
			events.turn = true and not events.blocked;
			events.side = Cube::LEFT; break;
		case GLFW_KEY_4:
			events.direction = false;
			events.turn = true and not events.blocked;
			events.side = Cube::BACK; break;
		case GLFW_KEY_5:
			events.direction = false;
			events.turn = true and not events.blocked;
			events.side = Cube::DOWN; break;
		case GLFW_KEY_6:
			events.direction = false;
			events.turn = true and not events.blocked;
			events.side = Cube::RIGHT; break;
		case GLFW_KEY_Q:
			events.direction = true;
			events.turn = true and not events.blocked;
			events.side = Cube::FRONT; break;
		case GLFW_KEY_W:
			events.direction = true;
			events.turn = true and not events.blocked;
			events.side = Cube::UP; break;
		case GLFW_KEY_E:
			events.direction = true;
			events.turn = true and not events.blocked;
			events.side = Cube::LEFT; break;
		case GLFW_KEY_R:
			events.direction = true;
			events.turn = true and not events.blocked;
			events.side = Cube::BACK; break;
		case GLFW_KEY_T:
			events.direction = true;
			events.turn = true and not events.blocked;
			events.side = Cube::DOWN; break;
		case GLFW_KEY_Y:
			events.direction = true;
			events.turn = true and not events.blocked;
			events.side = Cube::RIGHT; break;
		}

		else if (action == GLFW_RELEASE) switch (key) {
		case GLFW_KEY_SPACE:
			events.reset = false; break;
		case GLFW_KEY_1:
		case GLFW_KEY_2:
		case GLFW_KEY_3:
		case GLFW_KEY_4:
		case GLFW_KEY_5:
		case GLFW_KEY_6:
		case GLFW_KEY_Q:
		case GLFW_KEY_W:
		case GLFW_KEY_E:
		case GLFW_KEY_R:
		case GLFW_KEY_T:
		case GLFW_KEY_Y:
			events.turn = false; break;
		}
	}

	bool resized = false;

	void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		{
			extern Window window;
			window.width = width;
			window.height = height;
		}
		resized = true;
	}

	void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		// might not want to convert coordinates for framebuffer lookup
		mouse.pos = glm::vec2(float(-1.0 + 2.0 * xpos / width), float(1.0 - 2.0 * ypos / height));
	}

	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			if (action == GLFW_PRESS) {
				mouse.leftClick = true;
				events.leftClick = true;
			}
			else if (action == GLFW_RELEASE) {
				mouse.leftClick = false;
				events.leftClick = false;
			}
		}
	}

	Mouse mouse;

	Events events;

	bool shouldClose() {
		return window.shouldClose();
	}

	void update() {
		using namespace std::chrono;
		static auto oldTime = high_resolution_clock::now(), time = oldTime;
		static int frames = 0;
		mouse.prevPos = mouse.pos;
		window.update();
		mouse.velocity = mouse.pos - mouse.prevPos;
		frames++;
		auto now = high_resolution_clock::now();
		frameTime = (now - time).count();
		time = now;
		if (duration_cast<seconds>(now - oldTime) >= seconds{ 1 }) {
			fps = frames;
			oldTime = now;
			frames = 0;
			std::cout << fps << " fps" << std::endl;
		}
	}

	int fps = 0;
	long long frameTime = 0;
}
