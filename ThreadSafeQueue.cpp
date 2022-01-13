#include "ThreadSafeQueue.h"

bool ThreadSafeQueue::empty() const {
	return this->queue.empty();
}

void ThreadSafeQueue::push(const Move& m) {
	this->mutex.lock();
	this->queue.push(m);
	this->mutex.unlock();
}

Move ThreadSafeQueue::front() const {
	return this->queue.front();
}

void ThreadSafeQueue::pop() {
	this->mutex.lock();
	this->queue.pop();
	this->mutex.unlock();
}
