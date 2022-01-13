/*#include <GLFW/glfw3.h>
#include "Mouse.h"

extern Mouse mouse;

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	mouse.pos = mouse.nextPos;
	mouse.nextPos = glm::vec2(float(-1.0 + 2.0 * xpos / width), float(1.0 - 2.0 * ypos / height));
}*/
