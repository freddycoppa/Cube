#pragma once

#include <glm.hpp>

class Cube {
public:
	enum Side {
		FRONT = 0, GREEN  = 0, 
		UP    = 1, YELLOW = 1, 
		LEFT  = 2, RED    = 2, 
		BACK  = 3, BLUE   = 3, 
		DOWN  = 4, WHITE  = 4, 
		RIGHT = 5, ORANGE = 5,	
	};
	typedef Side Color;
	
	static constexpr bool CLOCKWISE = false, ANTICLOCKWISE = true;

	static glm::vec3 facePositions[6];

	struct Cubie {
		Color colors[6];
		Color& operator[](int index);
	} cubies[3][3][3];

	float colours[6][3][3];

private:
	void generateColors();
	void setColour(int x, int y, int z, int f);
	void rotation0(Side face, bool direction);
	void rotation1(Side face, bool direction);

public:
	Cube();
	void rotate(Side face, bool direction);
	void reset();
	void* data();
};
