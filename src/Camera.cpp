#include "Camera.h"
#include "events/EventDispatcher.h"

#include <GLFW/glfw3.h>

#include <functional>

void Camera::OnKeyMove(int keyCode)
{
	float distance = mMoveSensitivity * mDeltaFrameTime;
	if (distance == 0.0f)
	{
		distance = mMoveSensitivity;
	}
	if (keyCode == GLFW_KEY_W)
	{
		mEye += mDirection * distance;
	}
	if (keyCode == GLFW_KEY_S)
	{
		mEye -= mDirection * distance;
	}
	if (keyCode == GLFW_KEY_A)
	{
		mEye -= mRight * distance;
	}
	if (keyCode == GLFW_KEY_D)
	{
		mEye += mRight * distance;
	}
}

void Camera::UpdateCameraVectors()
{
	glm::vec3 direction(0.0f);
	direction.x = cos(glm::radians(mPitch)) * cos(glm::radians(mYaw));
	direction.y = sin(glm::radians(mPitch));
	direction.z = cos(glm::radians(mPitch)) * sin(glm::radians(mYaw));

	mDirection = glm::normalize(direction);
	mRight = glm::normalize(glm::cross(mDirection, mWorldUp));
	mUp = glm::normalize(glm::cross(mRight, mDirection));
}

glm::mat4 Camera::GetView() const
{
	glm::vec3 center = mEye + mDirection;
	return glm::lookAt(mEye, center, mUp);
}

glm::mat4 Camera::GetProjection(float aspect, float near, float far) const
{
	return glm::perspective(glm::radians(mZoom), aspect, near, far);
}

void Camera::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<EventKeyPressed>(std::bind(&Camera::OnEventKeyPressed, this, std::placeholders::_1));
	dispatcher.Dispatch<EventKeyRepeated>(std::bind(&Camera::OnEventKeyRepeated, this, std::placeholders::_1));
	dispatcher.Dispatch<EventCursorPosition>(std::bind(&Camera::OnEventCursorPosition, this, std::placeholders::_1));
	dispatcher.Dispatch<EventMouseScroll>(std::bind(&Camera::OnEventMouseScroll, this, std::placeholders::_1));
	dispatcher.Dispatch<EventFrameUpdate>(std::bind(&Camera::OnEventFrameUpdate, this, std::placeholders::_1));
}

void Camera::OnEventKeyPressed(EventKeyPressed& event)
{
	OnKeyMove(event.GetKey());
}

void Camera::OnEventKeyRepeated(EventKeyRepeated& event)
{
	OnKeyMove(event.GetKey());
}

void Camera::OnEventCursorPosition(EventCursorPosition& positionEvent)
{
	if (mLastXpos == 0.0f)
	{
		mLastXpos = positionEvent.GetXpos();
	}
	if (mLastYpos == 0.0f)
	{
		mLastYpos = positionEvent.GetYpos();
	}
	float pitch = (mLastYpos - positionEvent.GetYpos()) * mEulerSensitivity * mDeltaFrameTime;
	float yaw = (positionEvent.GetXpos() - mLastXpos) * mEulerSensitivity * mDeltaFrameTime;
	mPitch += pitch;
	mYaw += yaw;
	if (mPitch > 89.0f)
	{
		mPitch = 89.0f;
	}
	if (mPitch < -89.0f)
	{
		mPitch = -89.0f;
	}

	UpdateCameraVectors();

	mLastXpos = positionEvent.GetXpos();
	mLastYpos = positionEvent.GetYpos();
}

void Camera::OnEventMouseScroll(EventMouseScroll& scrollEvent)
{
	mZoom -= scrollEvent.GetYoffset() * mZoomSensitivity * mDeltaFrameTime;
	if (mZoom > 60.0f)
	{
		mZoom = 60.0f;
	}
	if (mZoom < 25.0f)
	{
		mZoom = 25.0f;
	}
}

void Camera::OnEventFrameUpdate(EventFrameUpdate& frameEvent)
{
	mDeltaFrameTime = frameEvent.GetDeltaTime();
}
