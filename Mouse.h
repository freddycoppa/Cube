#pragma once

#include <glm.hpp>

struct Mouse {
	glm::vec2 pos, nextPos, velocity;
	Mouse();
};
