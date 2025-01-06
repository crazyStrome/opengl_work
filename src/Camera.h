#pragma once

#include "events/Event.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>  
#include <glm/gtc/type_ptr.hpp>

static const float defaultMoveSensitivity = 0.0001f; // 移动灵敏度
static const float defaultZoomSensitivity = 0.03f; // 缩放灵敏度
static const float defaultEulerSensitivity = 0.01f; // 欧拉角灵敏度

class Camera {
private:
	glm::vec3 mEye; // 相机位置
	glm::vec3 mDirection; // 观察的方向
	glm::vec3 mUp; // 相机的上向量
	glm::vec3 mRight; // 相机的右向量
	glm::vec3 mWorldUp; // 世界的上向量

	float mMoveSensitivity; // 移动灵敏度
	float mZoomSensitivity; // 缩放灵敏度
	float mEulerSensitivity; // 欧拉角灵敏度

	double mDeltaFrameTime = 0.0f; // 帧间隔

	float mZoom = 45.0f; // 视角

	double mLastXpos = 0.0f; // 上一帧鼠标 x 坐标
	double mLastYpos = 0.0f; // 上一帧鼠标 y 坐标

	float mPitch = 0.0f; // 俯仰角
	float mYaw = -90.0f; // 偏航角

	void OnKeyMove(int keyCode);
	void UpdateCameraVectors();

	void OnEventKeyPressed(EventKeyPressed&);
	void OnEventKeyRepeated(EventKeyRepeated&);
	void OnEventCursorPosition(EventCursorPosition&);
	void OnEventMouseScroll(EventMouseScroll&);
	void OnEventFrameUpdate(EventFrameUpdate&);
public:
	Camera(const glm::vec3& eye = glm::vec3(0.0f, 0.0f, 2.0f),
		const glm::vec3& center = glm::vec3(0.0f, 0.0f, 0.0f),
		const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f),
		float moveSensitivity = defaultMoveSensitivity,
		float zoomSensitivity = defaultZoomSensitivity,
		float eulerSensitivity = defaultEulerSensitivity)
	: mEye(eye), mDirection(center - eye), mWorldUp(up),
		mMoveSensitivity(moveSensitivity), mZoomSensitivity(zoomSensitivity), mEulerSensitivity(eulerSensitivity)
	{
		UpdateCameraVectors();
	}

	glm::mat4 GetView() const;
	glm::mat4 GetProjection(float aspect, float near, float far) const;

	void OnEvent(Event&);
};
