#pragma once

#include "Cube.h"

struct Events {
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
};
