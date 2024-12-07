#pragma once

#include "Buffer.h"

class VertexArray {
private:
	unsigned int mVAO;
	int mAttribIndex;
public:
	VertexArray();

	void Bind() const;
	void UnBind() const;

	void AddVertexBuffer(const VertexBuffer&);
	void SetIndexBuffer(const IndexBuffer&);
};
