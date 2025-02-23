#include "Buffer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdexcept>

VertexBuffer::VertexBuffer(float* vertices, int size)
{
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
}

void VertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

IndexBuffer::IndexBuffer(unsigned int* indices, int size)
{
	glGenBuffers(1, &mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
}

void IndexBuffer::UnBind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

VertexLayout::VertexLayout()
	:mStride(0)
{
}

template<typename T>
void VertexLayout::AddAttrib(int, bool)
{
	throw new std::runtime_error("invalid type");
}

template<> void VertexLayout::AddAttrib<float>(int size, bool normalized) {
	mAttribs.push_back(VertexAttribData{
		size, GL_FLOAT, normalized, mStride,});
	mStride += size * int(sizeof(float));
}

