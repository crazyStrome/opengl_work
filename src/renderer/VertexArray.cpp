#include "VertexArray.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

VertexArray::VertexArray()
	:mAttribIndex(0)
{
	glGenVertexArrays(1, &mVAO);
}

void VertexArray::Bind() const
{
	glBindVertexArray(mVAO);
}

void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(const VertexBuffer& buffer)
{
	Bind();
	buffer.Bind();
	for (auto begin = buffer.Begin(); begin != buffer.End(); ++begin) {
		glEnableVertexAttribArray(mAttribIndex);
		glVertexAttribPointer(mAttribIndex, begin->size, begin->type, 
			begin->normalized? GL_TRUE: GL_FALSE,
			buffer.GetStride(), (void*)begin->offset);
		mAttribIndex++;
	}
	buffer.UnBind();
	UnBind();
}

void VertexArray::SetIndexBuffer(const IndexBuffer& buffer)
{
	Bind();
	buffer.Bind();
	UnBind();
	buffer.UnBind();
}
