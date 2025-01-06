#pragma once

#include "events/Event.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>  
#include <glm/gtc/type_ptr.hpp>

static const float defaultMoveSensitivity = 0.0001f; // �ƶ�������
static const float defaultZoomSensitivity = 0.03f; // ����������
static const float defaultEulerSensitivity = 0.01f; // ŷ����������

class Camera {
private:
	glm::vec3 mEye; // ���λ��
	glm::vec3 mDirection; // �۲�ķ���
	glm::vec3 mUp; // �����������
	glm::vec3 mRight; // �����������
	glm::vec3 mWorldUp; // �����������

	float mMoveSensitivity; // �ƶ�������
	float mZoomSensitivity; // ����������
	float mEulerSensitivity; // ŷ����������

	double mDeltaFrameTime = 0.0f; // ֡���

	float mZoom = 45.0f; // �ӽ�

	double mLastXpos = 0.0f; // ��һ֡��� x ����
	double mLastYpos = 0.0f; // ��һ֡��� y ����

	float mPitch = 0.0f; // ������
	float mYaw = -90.0f; // ƫ����

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
