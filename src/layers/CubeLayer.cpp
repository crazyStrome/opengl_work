#include "CubeLayer.h"

#include "renderer/Renderer.h"

#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>  
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

float vertices[] = {
	 0.5f, -0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,

	-0.5f, -0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,

	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,

	 0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,

	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f,  0.5f,
};

float textureCoord[] = {
	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,

	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,

	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,

	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,

	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,

	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,
};
unsigned int indices[] = {
	0, 1, 2,
	2, 3, 0,

	4, 5, 6,
	6, 7, 4,

	8, 9,10,
	10,11,8,

	12,13,14,
	14,15,12,

	16,17,18,
	18,19,16,

	20,21,22,
	22,23,20,
};

float borderColor[] = { 0.0f, 1.0f, 0.0f, 1.0f };

CubeLayer::CubeLayer()
	: mVertexBuffer(vertices, sizeof(vertices)),
	mTextureBuffer(textureCoord, sizeof(textureCoord)),
	mIndexBuffer(indices, sizeof(indices)),
	mVertexArray(),
	mShader("source/shader/hello_square.shader"),
	mTexture("source/picture/awesomeface.png",
		GL_LINEAR, GL_LINEAR,
		GL_CLAMP_TO_BORDER, GL_CLAMP_TO_EDGE,
		borderColor),
	mMatrix("source/picture/matrix.jpg",
		GL_LINEAR, GL_LINEAR,
		GL_CLAMP_TO_BORDER, GL_REPEAT,
		borderColor),
	mLast(0.0)
{
	VertexLayout layout;
	layout.AddAttrib<float>(3, false);
	mVertexBuffer.SetLayout(layout);

	VertexLayout textureLayout;
	textureLayout.AddAttrib<float>(2, false);
	mTextureBuffer.SetLayout(textureLayout);

	mVertexArray.AddVertexBuffer(mVertexBuffer);
	mVertexArray.AddVertexBuffer(mTextureBuffer);
	mVertexArray.SetIndexBuffer(mIndexBuffer);

	mShader.UnUse();
}

void CubeLayer::OnUpdate(const LayerUpdateArgs& args)
{
	mTexture.ActiveTexture(GL_TEXTURE1);
	mMatrix.ActiveTexture(GL_TEXTURE2);

	mShader.Use();
	mShader.SetUniform1i("ourTexture", 1);
	mShader.SetUniform1i("ourMatrix", 2);
	float offset = glfwGetTime();
	mShader.SetUniform1f("yOffset", offset);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.25f));
	model = glm::rotate(model, float(glfwGetTime()), glm::vec3(1.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	mShader.SetUniformMat4f("model", model);

	mShader.SetUniformMat4f("view", args.view);
	mShader.SetUniformMat4f("projection", args.projection);

	mVertexArray.Bind();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
	mShader.UnUse();
}

CubeLayer::~CubeLayer() {}
