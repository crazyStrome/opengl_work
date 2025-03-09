#include "CubeLayer.h"

#include "events/EventDispatcher.h"

#include "renderer/Renderer.h"

#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>  
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <functional>

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
	mBorderShader("source/shader/square_border.shader"),
	mTexture("source/picture/awesomeface.png",
		GL_LINEAR, GL_LINEAR,
		GL_CLAMP_TO_BORDER, GL_CLAMP_TO_EDGE,
		borderColor),
	mMatrix("source/picture/matrix.jpg",
		GL_LINEAR, GL_LINEAR,
		GL_CLAMP_TO_BORDER, GL_REPEAT,
		borderColor),
	mLast(0.0), mCursorXpos(0.0f), mCursorYpos(0.0f)
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

void CubeLayer::OnEventCursorPosition(EventCursorPosition& event)
{
	mCursorXpos = event.GetXpos();
	mCursorYpos = event.GetYpos();
}

void CubeLayer::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<EventCursorPosition>(std::bind(&CubeLayer::OnEventCursorPosition, this, std::placeholders::_1));
}

// getFootPoint p 到 ab 线的垂足点
static glm::vec3 getFootPoint(const glm::vec3& a, const glm::vec3& b,
    const glm::vec3& p) {
    glm::vec3 ab = b - a;
    double abModel = glm::dot(ab, ab);
    glm::vec3 ap = p - a;
    double apDotAb = glm::dot(ap, ab);
    float t = apDotAb / abModel;
    return a + ab * t;
}

void CubeLayer::OnUpdate(const LayerUpdateArgs& args)
{

	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilFunc(GL_ALWAYS, 1, 0xff);
	glStencilMask(0xff);

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

	float winX = mCursorXpos;
	float winY = float(args.windowHeight) - mCursorYpos;
	// 物体空间坐标系中的坐标
	glm::vec3 nearPos = glm::unProject(
		glm::vec3(winX, winY, args.nearZpos),
		args.view * model, args.projection,
		glm::vec4(0, 0, args.windowWidth, args.windowHeight)
	);
	glm::vec3 farPos = glm::unProject(
		glm::vec3(winX, winY, args.farZpos),
		args.view * model, args.projection,
		glm::vec4(0, 0, args.windowWidth, args.windowHeight)
	);
	// 在物体坐标系中，正方体的几何中心坐标
	glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
	bool colide = false;
	// 正方体几何中心到射线的垂足
	glm::vec3 footPoint = getFootPoint(nearPos, farPos, center);
	// 垂足如果在正方体内部，就检测到碰撞
	if ((footPoint.x >= -0.5f && footPoint.x <= 0.5f) &&
		(footPoint.y >= -0.5f && footPoint.y <= 0.5f) &&
		(footPoint.z >= -0.5f && footPoint.z <= 0.5f)) {
		glStencilFunc(GL_NOTEQUAL, 1, 0xff);
		glStencilMask(0x00); 

		mBorderShader.Use();
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		mBorderShader.SetUniformMat4f("model", model);
		mBorderShader.SetUniformMat4f("view", args.view);
		mBorderShader.SetUniformMat4f("projection", args.projection);


		mVertexArray.Bind();
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

		mBorderShader.UnUse();
		glStencilMask(0xFF);
	}
	glDisable(GL_STENCIL_TEST);
}

CubeLayer::~CubeLayer() {}
