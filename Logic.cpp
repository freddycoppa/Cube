#include "Logic.h"

#include <gtc/type_ptr.hpp>

using namespace glm;

float Logic::directions[2] = { -1.f, 1.f };

bool Logic::sideDirections[6] = { true, false, false, false, true, true };

void Logic::turn() {
	this->turning = true;
}

Logic::Logic(ThreadSafeQueue& queue, Cube& cube_, const long long& frameTime_, float speed_) : sideToBeRotated(0, 0, 0), sideRotation(1), turning(false), angle(0.f), da(0.f), moves(queue), cube(cube_), frameTime(frameTime_), speed(speed_) {}

void Logic::update() {
	if (turning) {
		sideToBeRotated = Cube::facePositions[move.side];
		float factor = (frameTime * speed) / 1000000000.f;
		angle += (da * factor);
		mat4 m(1);
		sideRotation = rotate(m, angle, sideToBeRotated);
		if (fabs(fabs(angle) - (pi<float>() / 2.f)) <= 0.125f * factor) {
			cube.rotate(move.side, move.direction);
			turning = false;
		}
	}
	else {
		if (not moves.empty()) {
			turning = true;
			move = moves.front();
			moves.pop();
			if (move.side == Cube::RED or move.side == Cube::YELLOW or move.side == Cube::BLUE) da = -0.125f;
			else da = +0.125f;
			bool dir = sideDirections[move.side];
			if (not move.direction) dir = !dir;
			move.direction = dir;
			da *= directions[move.direction];
		}
		angle = 0.f;
		sideToBeRotated = vec3(0, 0, 0);
		sideRotation = mat4(1);
	}
}

float* Logic::sideRotationPtr() {
	return value_ptr(this->sideRotation);
}

float* Logic::sideToBeRotatedPtr() {
	return value_ptr(this->sideToBeRotated);
}
