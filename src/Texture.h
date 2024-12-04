#pragma once

#include <string>
#include <stdexcept>
#include <iostream>

#include <glad/glad.h>
#include <stb/stb_image.h>


class Texture2D {
private:
	unsigned int mTextureID;
public:
	Texture2D(const std::string& name,
		int minFilter = GL_LINEAR,
		int magFilter = GL_LINEAR,
		int wrapS = GL_CLAMP_TO_BORDER,
		int wrapT = GL_CLAMP_TO_BORDER,
		float* borderColor = nullptr);
	void ActiveTexture(int textureUnit);
	void DeActiveTexture(int textureUnit);
	void Bind();
	void UnBind();
	~Texture2D();
	Texture2D(const Texture2D&) = delete;
	Texture2D& operator=(const Texture2D&) = delete;
	Texture2D(Texture2D&&);
	Texture2D& operator=(Texture2D&&);
};
