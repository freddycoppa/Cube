#pragma once

class Texture {
	unsigned texture;

public:
	Texture(unsigned char* data, int width, int height);
	void apply();
	~Texture();
};
