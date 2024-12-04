#include "Texture.h"

Texture2D::Texture2D(const std::string& name, 
	int minFilter, int magFilter, int wrapS, int wrapT,
	float* borderColor)
{
	int width, height, nchannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(name.c_str(), &width, &height, &nchannels, 0);
	if (!data)
	{
		std::cout << "Texture2D load picture: " << name << " error\n";
		throw new std::runtime_error("LOAD TEXTURE ERROR");
	}
	else
	{
		glGenTextures(1, &mTextureID);
		glBindTexture(GL_TEXTURE_2D, mTextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
		if (wrapS == GL_CLAMP_TO_BORDER || wrapT == GL_CLAMP_TO_BORDER)
		{
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		}
		int format = GL_RGBA;
		if (nchannels == 3)
		{
			format = GL_RGB;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);
	}
}

void Texture2D::ActiveTexture(int textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}

void Texture2D::DeActiveTexture(int textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind()
{
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}

void Texture2D::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &mTextureID);
	std::cout << "delete texture: " << mTextureID << std::endl;
	mTextureID = 0;
}

Texture2D::Texture2D(Texture2D&& right)
{
	if (&right == this)
	{
		return;
	}
	glDeleteTextures(1, &mTextureID);
	mTextureID = right.mTextureID;
	right.mTextureID = 0;
}

Texture2D& Texture2D::operator=(Texture2D&& right)
{
	if (&right == this)
	{
		return *this;
	}
	glDeleteTextures(1, &mTextureID);
	mTextureID = right.mTextureID;
	right.mTextureID = 0;
	return *this;
}
