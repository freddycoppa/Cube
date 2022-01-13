#pragma once

#include <glm.hpp>
#include <queue>
#include <random>
#include <chrono>
#include "Move.h"
#include <mutex>
#include "ThreadSafeQueue.h"

class Logic {
private:
	glm::vec3 sideToBeRotated;
	glm::mat4 sideRotation;
	Move move;
	float angle;
	float da;
	ThreadSafeQueue& moves;
	Cube& cube;
	const long long& frameTime;
	
	static float directions[2];
	static bool sideDirections[6];

	void turn();
public:
	bool turning;
	float speed;

	Logic(ThreadSafeQueue& queue, Cube& cube_, const long long& frameTime_, float speed_);
	void update();
	float* sideRotationPtr();
	float* sideToBeRotatedPtr();
};
