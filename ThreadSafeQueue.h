#pragma once

#include <queue>
#include <mutex>
#include "Move.h"

class ThreadSafeQueue {
	std::queue<Move> queue;
	std::mutex mutex;

public:
	bool empty() const;
	void push(const Move& m);
	Move front() const;
	void pop();
};
