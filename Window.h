#pragma once

#include <GLFW/glfw3.h>

struct Window {
	Window(int width, int height, const char* title, GLFWkeyfun keyCallback, GLFWframebuffersizefun frameBufferSizeCallback, GLFWcursorposfun cursorPosCallback, GLFWmousebuttonfun mouseButtonCallback);
	bool shouldClose() const;
	void update();
	~Window();
	float aspectRatio() const;

	unsigned int fps;
	double avgFPS;
	long long frameTime, second;

private:
	GLFWwindow* handle;
	void computeFPS();
};
