#include <vector>
#include "Texture.h"

template<typename T>using vector = std::vector<T>;

Texture genTexture(int width, int height, float radius, float power) {
	vector<unsigned char> image(width* height * 3);
	float boundary = powf(radius, power) /*radius*/;
	for (int i = 0; i < width; i++) for (int j = 0; j < height; j++) {
		unsigned int location = (i + (j * width)) * 3;
		float x = float(i) - (float(width) / 2);
		float y = float(j) - (float(height) / 2);
		if ((powf(x, power) + powf(y, power)) <= boundary) /*(abs(x) <= boundary and abs(y) <= boundary)*/ {
			image[location + 0] = 255;
			image[location + 1] = 255;
			image[location + 2] = 255;
		}
		else {
			image[location + 0] = 0;
			image[location + 1] = 0;
			image[location + 2] = 0;
		}
	}
	return Texture(&image[0], width, height);
}
