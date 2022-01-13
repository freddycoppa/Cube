/*#include <GLFW/glfw3.h>
#include "Events.h"

extern Events events;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) switch (key) {
	case GLFW_KEY_SPACE:
		events.reset = true;//and not events.blocked; 
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
}*/
