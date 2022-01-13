#include "Cube.h"

using namespace glm;

Cube::Color& Cube::Cubie::operator[](int index) {
	return this->colors[index];
}

vec3 Cube::facePositions[6] = {
	vec3( 0,  0,  1),
	vec3( 0,  1,  0),
	vec3(-1,  0,  0),
	vec3( 0,  0, -1),
	vec3( 0, -1,  0),
	vec3( 1,  0,  0),
};

void Cube::generateColors() {
	for (int x = 0; x < 3; x++) for (int y = 0; y < 3; y++) for (int z = 0; z < 3; z++) for (int f = 0; f < 6; f++) {
		vec3 vec = { x - 1, y - 1, z - 1 };
		vec3 face = facePositions[f];
		if (dot(face, vec) > 0) {
			float c = static_cast<float>(cubies[x][y][z][f]);
			if (face.x != 0) colours[f][y][z] = c;
			else if (face.y != 0) colours[f][x][z] = c;
			else colours[f][x][y] = c;
		}
	}
}

void Cube::setColour(int x, int y, int z, int f) {
	vec3 vec = { x - 1, y - 1, z - 1 };
	vec3 face = facePositions[f];
	if (dot(face, vec) > 0) {
		float c = static_cast<float>(cubies[x][y][z][f]);
		if (face.x != 0) colours[f][y][z] = c;
		else if (face.y != 0) colours[f][x][z] = c;
		else colours[f][x][y] = c;
	}
}

#define GENERATE_COLOURS for (int f = 0; f < 6; f++) setColour(x, y, z, f)

void Cube::rotation0(Side face, bool direction) {
	vec3 vec = facePositions[face];
	if (direction) {
		if (vec.x != 0) {
			int x = static_cast<int>(vec.x + 1);
			auto c = cubies[x][0][0];
			cubies[x][0][0] = cubies[x][0][2];
			cubies[x][0][2] = cubies[x][2][2];
			cubies[x][2][2] = cubies[x][2][0];
			cubies[x][2][0] = c;
			c = cubies[x][1][0];
			cubies[x][1][0] = cubies[x][0][1];
			cubies[x][0][1] = cubies[x][1][2];
			cubies[x][1][2] = cubies[x][2][1];
			cubies[x][2][1] = c;
			for (int y = 0; y < 3; y++) for (int z = 0; z < 3; z++) {
				auto c = cubies[x][y][z][DOWN];
				cubies[x][y][z][DOWN] = cubies[x][y][z][FRONT];
				cubies[x][y][z][FRONT] = cubies[x][y][z][UP];
				cubies[x][y][z][UP] = cubies[x][y][z][BACK];
				cubies[x][y][z][BACK] = c;
				GENERATE_COLOURS;
			}
		}
		else if (vec.y != 0) {
			int y = static_cast<int>(vec.y + 1);
			auto c = cubies[0][y][0];
			cubies[0][y][0] = cubies[0][y][2];
			cubies[0][y][2] = cubies[2][y][2];
			cubies[2][y][2] = cubies[2][y][0];
			cubies[2][y][0] = c;
			c = cubies[1][y][0];
			cubies[1][y][0] = cubies[0][y][1];
			cubies[0][y][1] = cubies[1][y][2];
			cubies[1][y][2] = cubies[2][y][1];
			cubies[2][y][1] = c;
			for (int z = 0; z < 3; z++) for (int x = 0; x < 3; x++) {
				auto c = cubies[x][y][z][FRONT];
				cubies[x][y][z][FRONT] = cubies[x][y][z][RIGHT];
				cubies[x][y][z][RIGHT] = cubies[x][y][z][BACK];
				cubies[x][y][z][BACK] = cubies[x][y][z][LEFT];
				cubies[x][y][z][LEFT] = c;
				GENERATE_COLOURS;
			}
		}
		else if (vec.z != 0) {
			int z = static_cast<int>(vec.z + 1);
			auto c = cubies[0][0][z];
			cubies[0][0][z] = cubies[0][2][z];
			cubies[0][2][z] = cubies[2][2][z];
			cubies[2][2][z] = cubies[2][0][z];
			cubies[2][0][z] = c;
			c = cubies[1][0][z];
			cubies[1][0][z] = cubies[0][1][z];
			cubies[0][1][z] = cubies[1][2][z];
			cubies[1][2][z] = cubies[2][1][z];
			cubies[2][1][z] = c;
			for (int x = 0; x < 3; x++) for (int y = 0; y < 3; y++) {
				auto c = cubies[x][y][z][DOWN];
				cubies[x][y][z][DOWN] = cubies[x][y][z][LEFT];
				cubies[x][y][z][LEFT] = cubies[x][y][z][UP];
				cubies[x][y][z][UP] = cubies[x][y][z][RIGHT];
				cubies[x][y][z][RIGHT] = c;
				GENERATE_COLOURS;
			}
		}
	}
	else {
		if (vec.x != 0) {
			int x = static_cast<int>(vec.x + 1);
			auto c = cubies[x][0][0];
			cubies[x][0][0] = cubies[x][2][0];
			cubies[x][2][0] = cubies[x][2][2];
			cubies[x][2][2] = cubies[x][0][2];
			cubies[x][0][2] = c;
			c = cubies[x][1][0];
			cubies[x][1][0] = cubies[x][2][1];
			cubies[x][2][1] = cubies[x][1][2];
			cubies[x][1][2] = cubies[x][0][1];
			cubies[x][0][1] = c;
			for (int y = 0; y < 3; y++) for (int z = 0; z < 3; z++) {
				auto c = cubies[x][y][z][DOWN];
				cubies[x][y][z][DOWN] = cubies[x][y][z][BACK];
				cubies[x][y][z][BACK] = cubies[x][y][z][UP];
				cubies[x][y][z][UP] = cubies[x][y][z][FRONT];
				cubies[x][y][z][FRONT] = c;
				GENERATE_COLOURS;
			}
		}
		else if (vec.y != 0) {
			int y = static_cast<int>(vec.y + 1);
			auto c = cubies[0][y][0];
			cubies[0][y][0] = cubies[2][y][0];
			cubies[2][y][0] = cubies[2][y][2];
			cubies[2][y][2] = cubies[0][y][2];
			cubies[0][y][2] = c;
			c = cubies[1][y][0];
			cubies[1][y][0] = cubies[2][y][1];
			cubies[2][y][1] = cubies[1][y][2];
			cubies[1][y][2] = cubies[0][y][1];
			cubies[0][y][1] = c;
			for (int z = 0; z < 3; z++) for (int x = 0; x < 3; x++) {
				auto c = cubies[x][y][z][FRONT];
				cubies[x][y][z][FRONT] = cubies[x][y][z][LEFT];
				cubies[x][y][z][LEFT] = cubies[x][y][z][BACK];
				cubies[x][y][z][BACK] = cubies[x][y][z][RIGHT];
				cubies[x][y][z][RIGHT] = c;
				GENERATE_COLOURS;
			}
		}
		else if (vec.z != 0) {
			int z = static_cast<int>(vec.z + 1);
			auto c = cubies[0][0][z];
			cubies[0][0][z] = cubies[2][0][z];
			cubies[2][0][z] = cubies[2][2][z];
			cubies[2][2][z] = cubies[0][2][z];
			cubies[0][2][z] = c;
			c = cubies[1][0][z];
			cubies[1][0][z] = cubies[2][1][z];
			cubies[2][1][z] = cubies[1][2][z];
			cubies[1][2][z] = cubies[0][1][z];
			cubies[0][1][z] = c;
			for (int x = 0; x < 3; x++) for (int y = 0; y < 3; y++) {
				auto c = cubies[x][y][z][DOWN];
				cubies[x][y][z][DOWN] = cubies[x][y][z][RIGHT];
				cubies[x][y][z][RIGHT] = cubies[x][y][z][UP];
				cubies[x][y][z][UP] = cubies[x][y][z][LEFT];
				cubies[x][y][z][LEFT] = c;
				GENERATE_COLOURS;
			}
		}
	}
}

void Cube::rotation1(Side face, bool direction) {
	vec3 vec = facePositions[face];
	if (direction) {
		if (vec.x != 0) {
			int x = static_cast<int>(vec.x + 1);
			for (int y = 0; y < 3; y++) for (int z = 0; z < 3; z++) {
				auto c = cubies[x][y][z][DOWN];
				cubies[x][y][z][DOWN] = cubies[x][y][z][FRONT];
				cubies[x][y][z][FRONT] = cubies[x][y][z][UP];
				cubies[x][y][z][UP] = cubies[x][y][z][BACK];
				cubies[x][y][z][BACK] = c;
				GENERATE_COLOURS;
			}
		}
		else if (vec.y != 0) {
			int y = static_cast<int>(vec.y + 1);
			for (int z = 0; z < 3; z++) for (int x = 0; x < 3; x++) {
				auto c = cubies[x][y][z][FRONT];
				cubies[x][y][z][FRONT] = cubies[x][y][z][RIGHT];
				cubies[x][y][z][RIGHT] = cubies[x][y][z][BACK];
				cubies[x][y][z][BACK] = cubies[x][y][z][LEFT];
				cubies[x][y][z][LEFT] = c;
				GENERATE_COLOURS;
			}
		}
		else if (vec.z != 0) {
			int z = static_cast<int>(vec.z + 1);
			for (int x = 0; x < 3; x++) for (int y = 0; y < 3; y++) {
				auto c = cubies[x][y][z][DOWN];
				cubies[x][y][z][DOWN] = cubies[x][y][z][LEFT];
				cubies[x][y][z][LEFT] = cubies[x][y][z][UP];
				cubies[x][y][z][UP] = cubies[x][y][z][RIGHT];
				cubies[x][y][z][RIGHT] = c;
				GENERATE_COLOURS;
			}
		}
	}
	else {
		if (vec.x != 0) {
			int x = static_cast<int>(vec.x + 1);
			for (int y = 0; y < 3; y++) for (int z = 0; z < 3; z++) {
				auto c = cubies[x][y][z][DOWN];
				cubies[x][y][z][DOWN] = cubies[x][y][z][BACK];
				cubies[x][y][z][BACK] = cubies[x][y][z][UP];
				cubies[x][y][z][UP] = cubies[x][y][z][FRONT];
				cubies[x][y][z][FRONT] = c;
				GENERATE_COLOURS;
			}
		}
		else if (vec.y != 0) {
			int y = static_cast<int>(vec.y + 1);
			for (int z = 0; z < 3; z++) for (int x = 0; x < 3; x++) {
				auto c = cubies[x][y][z][FRONT];
				cubies[x][y][z][FRONT] = cubies[x][y][z][LEFT];
				cubies[x][y][z][LEFT] = cubies[x][y][z][BACK];
				cubies[x][y][z][BACK] = cubies[x][y][z][RIGHT];
				cubies[x][y][z][RIGHT] = c;
				GENERATE_COLOURS;
			}
		}
		else if (vec.z != 0) {
			int z = static_cast<int>(vec.z + 1);
			for (int x = 0; x < 3; x++) for (int y = 0; y < 3; y++) {
				auto c = cubies[x][y][z][DOWN];
				cubies[x][y][z][DOWN] = cubies[x][y][z][RIGHT];
				cubies[x][y][z][RIGHT] = cubies[x][y][z][UP];
				cubies[x][y][z][UP] = cubies[x][y][z][LEFT];
				cubies[x][y][z][LEFT] = c;
				GENERATE_COLOURS;
			}
		}
	}
}

Cube::Cube() {
	/*for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				colours[i][j][k] = i;
			}
		}
	}*/

	this->reset();
}

void Cube::rotate(Side face, bool direction) {
	this->rotation0(face, direction);

/*#define mtx this->colours[face]

	Side adjacentSides[4] = {
		UP, LEFT, DOWN, RIGHT
	};

	if (direction*/ /*== ANTICLOCKWISE*//*) {
		float c = mtx[0][0];
		mtx[0][0] = mtx[0][2];
		mtx[0][2] = mtx[2][2];
		mtx[2][2] = mtx[2][0];
		mtx[2][0] = c;
		c = mtx[1][0];
		mtx[1][0] = mtx[0][1];
		mtx[0][1] = mtx[1][2];
		mtx[1][2] = mtx[2][1];
		mtx[2][1] = c;

		if (vec.x != 0) {
			int x = static_cast<int>(vec.x + 1);
			int right = (face + RIGHT) % 6;
			float layer[3] = {
				colours[right][x][0],
				colours[right][x][1],
				colours[right][x][2],
			};
			int current, previous;
			for (int i = 3; i > -1; i--) {
				current = (face + adjacentSides[i]) % 6;
				previous = (face + adjacentSides[(i + 3) % 4]) % 6;
				if (together(current, previous)) {
					colours[current][x][0] = colours[previous][x][0];
					colours[current][x][1] = colours[previous][x][1];
					colours[current][x][2] = colours[previous][x][2];
				}
				else {
					colours[current][x][0] = colours[previous][x][2];
					colours[current][x][1] = colours[previous][x][1];
					colours[current][x][2] = colours[previous][x][0];
				}
			}

			if (together(current, right)) {
				colours[current][x][0] = layer[0];
				colours[current][x][1] = layer[1];
				colours[current][x][2] = layer[2];
			}
			else {
				colours[current][x][0] = layer[2];
				colours[current][x][1] = layer[1];
				colours[current][x][2] = layer[0];
			}
		}

		else if (vec.z != 0) {
			int z = static_cast<int>(vec.z + 1);
			int right = (face + RIGHT) % 6;
			float layer[3] = {
				colours[right][0][z],
				colours[right][1][z],
				colours[right][2][z],
			};
			int current, previous;
			for (int i = 3; i > -1; i--) {
				current = (face + adjacentSides[i]) % 6;
				previous = (face + adjacentSides[(i + 3) % 4]) % 6;
				if (together(current, previous)) {
					colours[current][0][z] = colours[previous][0][z];
					colours[current][1][z] = colours[previous][1][z];
					colours[current][2][z] = colours[previous][2][z];
				}
				else {
					colours[current][0][z] = colours[previous][2][z];
					colours[current][1][z] = colours[previous][1][z];
					colours[current][2][z] = colours[previous][0][z];
				}
			}

			if (together(current, right)) {
				colours[current][0][z] = layer[0];
				colours[current][1][z] = layer[1];
				colours[current][2][z] = layer[2];
			}
			else {
				colours[current][0][z] = layer[2];
				colours[current][1][z] = layer[1];
				colours[current][2][z] = layer[0];
			}
		}

		else {
			int y = static_cast<int>(vec.y + 1);
			int right = (face + RIGHT) % 6;
			float layer[3];
			if (vec.x == facePositions[right].x) {
				layer[0] = colours[right][0][y];
				layer[1] = colours[right][1][y];
				layer[2] = colours[right][2][y];
			}
			else*/ /*if (vec.z == facePositions[right].z)*/ /*{
				layer[0] = colours[right][y][0];
				layer[1] = colours[right][y][1];
				layer[2] = colours[right][y][2];
			}

			int current, previous;
			for (int i = 3; i > -1; i--) {
				current = (face + adjacentSides[i]) % 6;
				previous = (face + adjacentSides[(i + 3) % 4]) % 6;
				if (together(current, previous)) {
					if (vec.x == facePositions[current].x) {
						colours[current][0][y] = colours[previous][y][0];
						colours[current][1][y] = colours[previous][y][1];
						colours[current][2][y] = colours[previous][y][2];
					}
					else*/ /*if (vec.z == facePositions[current].z)*/ /*{
						colours[current][y][0] = colours[previous][0][y];
						colours[current][y][1] = colours[previous][1][y];
						colours[current][y][2] = colours[previous][2][y];
					}
				}
				else {
					if (vec.x == facePositions[current].x) {
						colours[current][0][y] = colours[previous][y][2];
						colours[current][1][y] = colours[previous][y][1];
						colours[current][2][y] = colours[previous][y][0];
					}
					else*/ /*if (vec.z == facePositions[current].z)*/ /*{
						colours[current][y][0] = colours[previous][2][y];
						colours[current][y][1] = colours[previous][1][y];
						colours[current][y][2] = colours[previous][0][y];
					}
				}
			}

			if (together(current, right)) {
				if (vec.x == facePositions[current].x) {
					colours[current][0][y] = layer[0];
					colours[current][1][y] = layer[1];
					colours[current][2][y] = layer[2];
				}
				else*/ /*if (vec.z == facePositions[current].z)*/ /*{
					colours[current][y][0] = layer[0];
					colours[current][y][1] = layer[1];
					colours[current][y][2] = layer[2];
				}
			}
			else {
				if (vec.x == facePositions[current].x) {
					colours[current][0][y] = layer[2];
					colours[current][1][y] = layer[1];
					colours[current][2][y] = layer[0];
				}
				else*/ /*if (vec.z == facePositions[current].z)*/ /*{
					colours[current][y][0] = layer[2];
					colours[current][y][1] = layer[1];
					colours[current][y][2] = layer[0];
				}
			}
		}
	}

	else*/ /*if (direction == CLOCKWISE)*/ /*{
		float c = mtx[0][0];
		mtx[0][0] = mtx[2][0];
		mtx[2][0] = mtx[2][2];
		mtx[2][2] = mtx[0][2];
		mtx[0][2] = c;
		c = mtx[1][0];
		mtx[1][0] = mtx[2][1];
		mtx[2][1] = mtx[1][2];
		mtx[1][2] = mtx[0][1];
		mtx[0][1] = c;

		if (vec.x != 0) {
			int x = vec.x + 1;
			int up = (face + UP) % 6;
			float layer[3] = {
				colours[up][x][0],
				colours[up][x][1],
				colours[up][x][2],
			};
			int current, next;
			for (int i = 0; i < 4; i++) {
				current = (face + adjacentSides[i]) % 6;
				next = (face + adjacentSides[(i + 1) % 4]) % 6;
				if (together(current, next)) {
					colours[current][x][0] = colours[next][x][0];
					colours[current][x][1] = colours[next][x][1];
					colours[current][x][2] = colours[next][x][2];
				}
				else {
					colours[current][x][0] = colours[next][x][2];
					colours[current][x][1] = colours[next][x][1];
					colours[current][x][2] = colours[next][x][0];
				}
			}

			if (together(current, up)) {
				colours[current][x][0] = layer[0];
				colours[current][x][1] = layer[1];
				colours[current][x][2] = layer[2];
			}
			else {
				colours[current][x][0] = layer[2];
				colours[current][x][1] = layer[1];
				colours[current][x][2] = layer[0];
			}
		}

		else if (vec.z != 0) {
			int z = vec.z + 1;
			int up = (face + UP) % 6;
			float layer[3] = {
				colours[up][0][z],
				colours[up][1][z],
				colours[up][2][z],
			};
			int current, next;
			for (int i = 0; i < 4; i++) {
				current = (face + adjacentSides[i]) % 6;
				next = (face + adjacentSides[(i + 1) % 4]) % 6;
				if (together(current, next)) {
					colours[current][0][z] = colours[next][0][z];
					colours[current][1][z] = colours[next][1][z];
					colours[current][2][z] = colours[next][2][z];
				}
				else {
					colours[current][0][z] = colours[next][2][z];
					colours[current][1][z] = colours[next][1][z];
					colours[current][2][z] = colours[next][0][z];
				}
			}

			if (together(current, up)) {
				colours[current][0][z] = layer[0];
				colours[current][1][z] = layer[1];
				colours[current][2][z] = layer[2];
			}
			else {
				colours[current][0][z] = layer[2];
				colours[current][1][z] = layer[1];
				colours[current][2][z] = layer[0];
			}
		}

		else {
			int y = vec.y + 1;
			int up = (face + UP) % 6;
			float layer[3];
			if (vec.x == facePositions[up].x) {
				layer[0] = colours[up][0][y];
				layer[1] = colours[up][1][y];
				layer[2] = colours[up][2][y];
			}
			else*/ /*if (vec.z == facePositions[up].z)*/ /*{
				layer[0] = colours[up][y][0];
				layer[1] = colours[up][y][1];
				layer[2] = colours[up][y][2];
			}

			int current, next;
			for (int i = 0; i < 4; i++) {
				current = (face + adjacentSides[i]) % 6;
				next = (face + adjacentSides[(i + 1) % 4]) % 6;
				if (together(current, next)) {
					if (vec.x == facePositions[current].x) {
						colours[current][0][y] = colours[next][y][0];
						colours[current][1][y] = colours[next][y][1];
						colours[current][2][y] = colours[next][y][2];
					}
					else*/ /*if (vec.z == facePositions[current].z)*/ /*{
						colours[current][y][0] = colours[next][0][y];
						colours[current][y][1] = colours[next][1][y];
						colours[current][y][2] = colours[next][2][y];
					}
				}
				else {
					if (vec.x == facePositions[current].x) {
						colours[current][0][y] = colours[next][y][2];
						colours[current][1][y] = colours[next][y][1];
						colours[current][2][y] = colours[next][y][0];
					}
					else*/ /*if (vec.z == facePositions[current].z)*/ /*{
						colours[current][y][0] = colours[next][2][y];
						colours[current][y][1] = colours[next][1][y];
						colours[current][y][2] = colours[next][0][y];
					}
				}
			}

			if (together(current, up)) {
				if (vec.x == facePositions[current].x) {
					colours[current][0][y] = layer[0];
					colours[current][1][y] = layer[1];
					colours[current][2][y] = layer[2];
				}
				else*/ /*if (vec.z == facePositions[current].z)*/ /*{
					colours[current][y][0] = layer[0];
					colours[current][y][1] = layer[1];
					colours[current][y][2] = layer[2];
				}
			}
			else {
				if (vec.x == facePositions[current].x) {
					colours[current][0][y] = layer[2];
					colours[current][1][y] = layer[1];
					colours[current][2][y] = layer[0];
				}
				else*/ /*if (vec.z == facePositions[current].z)*/ /*{
					colours[current][y][0] = layer[2];
					colours[current][y][1] = layer[1];
					colours[current][y][2] = layer[0];
				}
			}
		}
    }*/

	//this->generateColors();
}

void Cube::reset() {
	for (int x = 0; x < 3; x++) for (int y = 0; y < 3; y++) for (int z = 0; z < 3; z++) for (int f = 0; f < 6; f++) {
		vec3 vec = { x - 1, y - 1, z - 1 };
		vec3 face = facePositions[f];
		if (dot(vec, face) > 0) {
			this->cubies[x][y][z][f] = static_cast<Color>(f);
			float c = static_cast<float>(f);
			if (face.x != 0) colours[f][y][z] = c;
			else if (face.y != 0) colours[f][x][z] = c;
			else colours[f][x][y] = c;
		}
		else this->cubies[x][y][z][f] = static_cast<Color>(-1);
		this->cubies[x][y][z][f] = static_cast<Color>(f);
	}
}

void* Cube::data() {
	return this->colours;
}
