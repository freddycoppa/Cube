#include <GL/glew.h>
#include "Window.h"
#include <exception>
#include <chrono>

Window::Window(int width, int height, const char* title, GLFWkeyfun keyCallback, GLFWframebuffersizefun frameBufferSizeCallback, GLFWcursorposfun cursorPosCallback, GLFWmousebuttonfun mouseButtonCallback) :
	fps(0), avgFPS(0), frameTime(0l), second(0l) {
	if (!glfwInit()) throw std::exception("Failed to initialize GLFW!");
	glfwWindowHint(GLFW_SAMPLES, 4);
	this->handle = glfwCreateWindow(width, height, title, NULL, NULL);
	if (this->handle == NULL) throw std::exception("Failed to create window!");
	glfwSetKeyCallback(this->handle, keyCallback);
	glfwSetFramebufferSizeCallback(this->handle, frameBufferSizeCallback);
	glfwSetCursorPosCallback(this->handle, cursorPosCallback);
	glfwSetMouseButtonCallback(this->handle, mouseButtonCallback);
	glfwSetCursorPos(this->handle, width / 2., height / 2.);
	glfwMakeContextCurrent(this->handle);
	if (glewInit() != GLEW_OK) throw std::exception("Failed to initialize OpenGL!");
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//glClearColor(1, 1, 1, 1);
	//glCullFace(GL_BACK);
	glEnable(GL_MULTISAMPLE);
}

bool Window::shouldClose() const {
	return glfwWindowShouldClose(this->handle);
}

void Window::update() {
	glfwSwapBuffers(this->handle);
	glfwPollEvents();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	this->computeFPS();
}

Window::~Window() {
	glfwTerminate();
}

float Window::aspectRatio() const {
	int width, height;
	glfwGetFramebufferSize(this->handle, &width, &height);
	return float(width) / float(height);
}

void Window::computeFPS() {
	using namespace std::chrono;
	static auto oldTime = high_resolution_clock::now(), time = oldTime;
	static int fps = 0;
	fps++;
	auto now = high_resolution_clock::now();
	this->frameTime = (now - time).count();
	time = now;
	if (duration_cast<seconds>(now - oldTime) >= seconds{ 1 }) {
		this->fps = fps;
		this->avgFPS *= this->second;
		this->avgFPS += this->fps;
		this->second++;
		this->avgFPS /= double(this->second);
		oldTime = now;
		fps = 0;
	}
}
